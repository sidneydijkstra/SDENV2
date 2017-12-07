#include "renderer.h"


// renderer constructor
Renderer::Renderer(){
	fontloader = new FontLoader();

	framebufferQuad = new Mesh();
	framebufferQuad->loadQuad();
}

void Renderer::renderScene(Scene * scene, Shader* shader2D, Shader* shader3D) {
	int childcount = scene->getChildCount();
	std::vector<Mesh*> childeren = scene->getChilderen();
	if (scene->getSceneMode() == SCENE2D) { // if scene 2d
		shader2D->use();
		for (int i = 0; i < childcount; i++) {
			this->render2D(childeren[i], shader2D, scene);
		}
	}
	else { // if scene 3d
		shader3D->use();
		for (int i = 0; i < childcount; i++) {
			this->render3D(childeren[i], shader3D, scene);
		}
	}
}

void Renderer::render3D(Mesh* mesh, Shader* shader, Scene* scene) {
	// bind VAO
	glBindVertexArray(mesh->_VAO);

	// activate textures
	if (mesh->sprite()->getTexture() != NULL) {
		shader->setBool("doTexture", true);

		if (mesh->spriteAnimator() != NULL) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->spriteAnimator()->getCurrentAnimation());
		}else{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->sprite()->getTexture());
		}

	}else {
		shader->setBool("doTexture", false);
	}

	// get model matrix
	glm::mat4 model;
	model = glm::translate(model, mesh->position);						// position
	model = glm::scale(model, mesh->scale);								// scale
	model = glm::rotate(model, mesh->rotation.x, glm::vec3(1, 0, 0));	// rotation x
	model = glm::rotate(model, mesh->rotation.y, glm::vec3(0, 1, 0));	// rotation y
	model = glm::rotate(model, mesh->rotation.z, glm::vec3(0, 0, 1));	// rotation z

	// get view
	glm::mat4 view = glm::lookAt(scene->getCamera()->position, scene->getCamera()->position + scene->getCamera()->front, scene->getCamera()->up); // render 3D

	// get projectioins
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)SWIDTH / (GLfloat)SHEIGHT, 0.001f, 100.0f); // render 3D

	// set uniforms
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	// set object color uniform
	shader->setVec3("fragObjectColor", mesh->color.getColor());

	// set lighting uniforms
	if(scene->getLight() != NULL){
		shader->setBool("doLighting", true);

		shader->setVec3("light.color", scene->getLight()->lightColor);
		shader->setVec3("light.position", scene->getLight()->position);
		shader->setVec3("light.viewPosition", scene->getCamera()->position);

		shader->setFloat("light.ambientStrength", scene->getLight()->ambientStrength);
		shader->setFloat("light.specularStrength", scene->getLight()->specularStrength);
	}else {
		shader->setBool("doLighting", false);
	}

	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, mesh->_drawsize);
	glBindVertexArray(0);
}

void Renderer::render2D(Mesh* mesh, Shader* shader, Scene* scene) {
	// bind VAO
	glBindVertexArray(mesh->_VAO);

	// activate textures
	if (mesh->sprite()->getTexture() != NULL) {
		shader->setBool("doTexture", true);

		if (mesh->spriteAnimator() != NULL) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->spriteAnimator()->getCurrentAnimation());
		}else{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->sprite()->getTexture());
		}

	}else {
		shader->setBool("doTexture", false);
	}

	// get model matrix
	glm::mat4 model;
	model = glm::translate(model, mesh->position);						// position
	model = glm::scale(model, mesh->scale);								// scale
	model = glm::rotate(model, mesh->rotation.x, glm::vec3(1, 0, 0));	// rotation x
	model = glm::rotate(model, mesh->rotation.y, glm::vec3(0, 1, 0));	// rotation y
	model = glm::rotate(model, mesh->rotation.z, glm::vec3(0, 0, 1));	// rotation z

	glm::mat4 projection = glm::ortho(0.0f, (float)SWIDTH, 0.0f, (float)SHEIGHT, 0.0f, 1.0f); // render 2D

	// set uniforms
	shader->setMat4("model", model);
	shader->setMat4("projection", projection);

	// set object color uniform
	shader->setVec3("fragObjectColor", mesh->color.getColor());

	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, mesh->_drawsize);
	glBindVertexArray(0);
}

void Renderer::renderFramebuffer(FrameBuffer * framebuffer, Shader * shader){
	// set shader, frame buffer options and bind texture
	shader->use();
	glBindVertexArray(framebufferQuad->_VAO);
	glBindTexture(GL_TEXTURE_2D, framebuffer->getFrameBufferNormalTexture());

	// get model
	glm::mat4 model;
	model = glm::translate(model, framebuffer->position);
	model = glm::scale(model, framebuffer->size);
	model = glm::rotate(model, framebuffer->rotation.x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, framebuffer->rotation.y, glm::vec3(0, 1, 0));
	model = glm::rotate(model, framebuffer->rotation.z, glm::vec3(0, 0, 1));

	// get projectioins
	glm::mat4 projection = glm::ortho(0.0f, (float)SWIDTH, 0.0f, (float)SHEIGHT, 0.0f, 1.0f); // render 2D

	// set shader uniforms
	framebuffer->shader()->setMat4("model", model);
	framebuffer->shader()->setMat4("projection", projection);

	// draw framebuffer on quad
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Renderer::renderText(Shader* shader, Text* text){
	// set text color
	shader->setVec3("textColor", text->color);

	// set texture and VAO
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(text->_VAO);

	// get message scale and position
	std::string str = text->message;
	float scale = text->scale;
	float x = text->position.x;
	float y = text->position.y;

	// Iterate through all characters
	std::string::const_iterator c;
	int i = 0;
	for (c = str.begin(); c != str.end(); c++){
		// if lerp color set new color
		i++;
		if (text->doColorLerp()) {
			shader->setVec3("textColor", text->getColorLerp(i));
		}

		// get charackter
		Character ch = fontloader->getFont(text->getFont())[*c];

		// set pos
		GLfloat xpos = x + ch.bearing.x * scale;
		GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

		// set width and height
		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;

		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};

		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, text->_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

// renderer deconstructor
Renderer::~Renderer() {
	// delete scene manager and framebufferQuad
	delete fontloader;
	delete framebufferQuad;
}

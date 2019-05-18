#include "renderer.h"


// renderer constructor
Renderer::Renderer(){
	_fontloader = new FontLoader();
	_resmanager = new Resourcemanager();

	framebufferQuad = new Mesh();
	framebufferQuad->loadQuad();
}

void Renderer::renderScene(Scene * scene, Shader* shader2D, Shader* shader3D) {
	int childcount = scene->getChildCount();
	std::vector<Entity*> childeren = scene->getChilderen();
	if (scene->getSceneMode() == SCENE2D) { // if scene 2d
		shader2D->use();
		for (int i = 0; i < childcount; i++) {
			this->render2D(childeren[i], shader2D, scene, glm::vec3(0.0f));
		}
	}
	else { // if scene 3d
		shader3D->use();
		for (int i = 0; i < childcount; i++) {
			this->render3D(childeren[i], shader3D, scene, glm::vec3(0.0f));
		}
	}

	/*Line* l = new Line();
	l->addPoint(childeren[1]->position);
	l->addPoint(childeren[0]->position);
	l->addPoint(childeren[0]->position);
	l->addPoint(childeren[2]->position);
	l->addPoint(childeren[2]->position);
	l->addPoint(childeren[1]->position);

	this->renderLine(shader2D, l);

	delete l;*/
}

void Renderer::render3D(Entity* entity, Shader* shader, Scene* scene, glm::vec3 parentPosition) {
	// get new pos of entity
	glm::vec3 pos = entity->position + parentPosition;

	// only render entity if entity is active
	if(entity->active){
		// bind VAO
		glBindVertexArray(entity->mesh()->_VAO);

		// activate textures
		if (entity->sprite()->texture() != NULL) {
			shader->setBool("doTexture", true);

			if (entity->spriteAnimator() != NULL) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, _resmanager->getTexture(entity->spriteAnimator()->getCurrentAnimation(), entity->spriteAnimator()->filter(), entity->spriteAnimator()->wraping()));
			}else{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, _resmanager->getTexture(entity->sprite()->texture(), entity->sprite()->filter(), entity->sprite()->wraping()));
			}

		}else {
			shader->setBool("doTexture", false);
		}

		// get model matrix
		glm::mat4 model;
		model = glm::translate(model, pos);									// position
		model = glm::scale(model, entity->scale);							// scale
		model = glm::rotate(model, entity->rotation.x, glm::vec3(1, 0, 0));	// rotation x
		model = glm::rotate(model, entity->rotation.y, glm::vec3(0, 1, 0));	// rotation y
		model = glm::rotate(model, entity->rotation.z, glm::vec3(0, 0, 1));	// rotation z

		// get view
		glm::mat4 view = glm::lookAt(scene->camera()->position, scene->camera()->position + scene->camera()->front, scene->camera()->up); // render 3D

		// get projectioins
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)SWIDTH / (GLfloat)SHEIGHT, 0.001f, 100.0f); // render 3D


		// create model view projection matrix
		glm::mat4 MVP = projection * view * model;

		// set MVP uniforms
		shader->setMat4("MVP", MVP);

		// set model uniforms
		shader->setMat4("model", model); // <-- 3D rendering needs this for normals

		// set object color uniform
		shader->setVec3("fragObjectColor", entity->color.getColor());

		// set lighting uniforms
		if(scene->getLight() != NULL){
			shader->setBool("doLighting", true);

			shader->setVec3("light.color", scene->getLight()->lightColor);
			shader->setVec3("light.position", scene->getLight()->position);
			shader->setVec3("light.viewPosition", scene->camera()->position);

			shader->setFloat("light.ambientStrength", scene->getLight()->ambientStrength);
			shader->setFloat("light.specularStrength", scene->getLight()->specularStrength);
		}else {
			shader->setBool("doLighting", false);
		}

		// draw cube
		glDrawArrays(GL_TRIANGLES, 0, entity->mesh()->_drawsize);
		glBindVertexArray(0);
	}

	// render all childeren of entity
	if (entity->getChildCount() > 0) {
		std::vector<Entity*> childeren = entity->getChilderen();
		std::cout << childeren.size() << std::endl;
		for (int i = 0; i < childeren.size(); i++){
			this->render3D(childeren[i], shader, scene, pos);
		}
	}
}

void Renderer::render2D(Entity* entity, Shader* shader, Scene* scene, glm::vec3 parentPosition) {
	if (entity == NULL) {
		return;
	}

	// get new pos of entity
	glm::vec3 pos = entity->position + parentPosition;

	// only render entity if entity is active
	if(entity->active){
		// bind VAO

		if (entity->mesh() == NULL) {
			return;
		}

		glBindVertexArray(entity->mesh()->_VAO);

		// activate textures
		if (entity->sprite()->texture() != NULL || entity->spriteAnimator() != NULL) {
			shader->setBool("doTexture", true);

			if (entity->spriteAnimator() != NULL) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, _resmanager->getTexture(entity->spriteAnimator()->getCurrentAnimation(), entity->spriteAnimator()->filter(), entity->spriteAnimator()->wraping()));
			}else{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, _resmanager->getTexture(entity->sprite()->texture(), entity->sprite()->filter(), entity->sprite()->wraping()));
			}

		}else {
			shader->setBool("doTexture", false);
		}

		// get model matrix
		glm::mat4 model;
		model = glm::translate(model, pos);									// position
		model = glm::scale(model, entity->scale * entity->size);			// size ( with scale )
		model = glm::rotate(model, entity->rotation.x, glm::vec3(1, 0, 0));	// rotation x
		model = glm::rotate(model, entity->rotation.y, glm::vec3(0, 1, 0));	// rotation y
		model = glm::rotate(model, entity->rotation.z, glm::vec3(0, 0, 1));	// rotation z
	
		// get view
		glm::mat4 view = glm::lookAt(scene->camera()->position, scene->camera()->position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

		// get projection
		glm::mat4 projection = glm::ortho(0.0f, (float)SWIDTH, 0.0f, (float)SHEIGHT, 0.0f, 1.0f);

		// create model view projection matrix
		glm::mat4 MVP = projection * view * model;

		// set MVP uniforms
		shader->setMat4("MVP", MVP);

		// set object color uniform
		shader->setVec3("fragObjectColor", entity->color.getColor());

		// draw cube
		glDrawArrays(GL_TRIANGLES, 0, entity->mesh()->_drawsize);
		glBindVertexArray(0);
	}

	// render all childeren of entity
	if (entity->getChildCount() > 0) {
		std::vector<Entity*> c = entity->getChilderen();
		for (int i = 0; i < c.size(); i++) {
			this->render2D(c[i], shader, scene, pos);
		}
	}
}

void Renderer::renderFramebuffer(FrameBuffer * framebuffer, Shader * shader){
	// use framebuffer shader, frame buffer options and bind texture
	framebuffer->shader()->use();
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
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::renderUIText(UIText* text, UICollection* parent, Shader* shader){
	shader->setVec3("textColor", text->color);

	// set texture and VAO
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(text->_VAO);


	std::string::const_iterator c;
	std::string str = text->message;
	float scale = text->scale;

	float x = 0;
	float y = 0;
	// get message scale and position
	if (text->center) {
		// get width and height
		float w = 0;
		float h = 0;
		for (c = str.begin(); c != str.end(); c++) {
			Character ch = _fontloader->getFont(text->getFont())[*c];
			w += ch.size.x * scale;
			h = (ch.size.y * scale) > h ? ch.size.y * scale : h;
		}

		x = (text->position.x + parent->position.x) - w / 2;
		y = (text->position.y + parent->position.y) - h / 2; //(text->position.y - SHEIGHT) * -1 + parent->position.x;

		x -= 6; // <-- a small offset
	}else {
		x = (text->position.x + parent->position.x);
		y = (text->position.y + parent->position.y); //(text->position.y - SHEIGHT) * -1 + parent->position.x;
	}

	// Iterate through all characters
	int i = 0;
	for (c = str.begin(); c != str.end(); c++){
		// if lerp color set new color
		i++;
		if (text->doColorLerp()) {
			shader->setVec3("textColor", text->getColorLerp(i));
		}

		// get charackter
		Character ch = _fontloader->getFont(text->getFont())[*c];

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

void Renderer::RenderCanvas(Canvas * canvas, Shader * shader, Shader* textShader){
	// if not active return
	if (!canvas->active) {
		return;
	}

	// render all the UICollections in the childeren
	int size = canvas->getChildCount();
	std::vector<UICollection*> collection = canvas->getAllChilderen();
	for (int i = 0; i < size; i++) {
		this->renderUICollection(collection[i], shader, textShader);
	}
}

void Renderer::renderUICollection(UICollection * collection, Shader * shader, Shader* textShader){
	// if not active return
	if (!collection->active) {
		return;
	}

	// render all the UIElements in the collection
	int size = collection->getElementsCount();
	std::vector<UIElement*> elements = collection->getAllElements();
	for (int i = 0; i < size; i++){
		shader->use();
		this->renderUIElement(elements[i], collection, shader);
	}

	// render all the UIText in the collection
	size = collection->getUITextCount();
	std::vector<UIText*> texts = collection->getAllUIText();
	for (int i = 0; i < size; i++) {
		textShader->use();
		this->renderUIText(texts[i], collection, textShader);
	}
}


void Renderer::renderUIElement(UIElement * element, UICollection* parent, Shader * shader){
	// only render entity if entity is active
	if (element->active) {
		// set parent pos
		glm::vec3 pos = element->position + parent->position;

		// bind VAO
		glBindVertexArray(element->mesh()->_VAO);

		// activate textures
		if (element->sprite()->texture() != NULL) {
			shader->setBool("doTexture", true);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _resmanager->getTexture(element->sprite()->texture(), element->sprite()->filter(), element->sprite()->wraping()));
		}
		else {
			shader->setBool("doTexture", false);
		}

		// create and set model matrix
		glm::mat4 model;
		model = glm::translate(model, pos);
		model = glm::scale(model, element->size);
		model = glm::rotate(model, element->rotation.x, glm::vec3(1, 0, 0));
		model = glm::rotate(model, element->rotation.y, glm::vec3(0, 1, 0));
		model = glm::rotate(model, element->rotation.z, glm::vec3(0, 0, 1));

		shader->setMat4("model", model);

		// set object color uniform
		shader->setVec3("fragObjectColor", element->color.getColor());

		// draw cube
		glDrawArrays(GL_TRIANGLES, 0, element->mesh()->_drawsize);
		glBindVertexArray(0);
	}
}

void Renderer::renderLine(Shader* shader, Line* line){

	GLuint _VAO;
	GLuint _VBO;

	// get points in vertice

	std::vector<glm::vec3> points = line->getPoints();

	std::vector<float> verts = std::vector<float>();

	GLfloat *vertices = new GLfloat[points.size() * 4];

	for (int i = 0; i < points.size(); i++){
		glm::vec3 pos = points[i];

		vertices[i * 4 + 0] = pos.x;
		vertices[i * 4 + 1] = pos.y;

		vertices[i * 4 + 2] = 0.0f;
		vertices[i * 4 + 3] = 1.0f;

		if (i+1 & 2 == 0 && i+1 > points.size()) {
			/*verts.push_back(pos.x);
			verts.push_back(pos.y);

			verts.push_back(0.0f);
			verts.push_back(1.0f);*/
		}
	}

	/*float vertices[] = {
		points[0].x, points[0].y,  0.0f, 1.0f,
		points[1].x, points[1].y,  0.0f, 1.0f,
	};*/

	int _drawsize = points.size() * 4 * sizeof(GLfloat);

	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _drawsize, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	// use shader
	shader->use();

	// bind VAO
	glBindVertexArray(_VAO);

	// get model matrix
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0,0,0));
	model = glm::scale(model, glm::vec3(1,1,0));

	glm::mat4 projection = glm::ortho(0.0f, (float)SWIDTH, 0.0f, (float)SHEIGHT, 0.0f, 1.0f); // render 2D
	
	// give model and projection to shader
	shader->setMat4("model", model);
	shader->setMat4("projection", projection);

	// set doTextures to false
	shader->setBool("doTexture", false);

	// give object color to shader
	shader->setVec3("fragObjectColor", Color(0,255,0).getColor());
	
	// draw cube
	glLineWidth(20.0f);
	glDrawArrays(GL_LINES, 0, _drawsize);
	glBindVertexArray(0);
}

// renderer deconstructor
Renderer::~Renderer() {
	// delete scene manager and framebufferQuad
	delete _fontloader;
	delete framebufferQuad;
	delete _resmanager;
}

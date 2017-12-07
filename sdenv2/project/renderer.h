
#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <map>

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// include freetype
#include <ft2build.h>
#include FT_FREETYPE_H  

// include config
#include "sdenv2config.h"

// include shader
#include "shader.h"
// include scene
#include "scene.h"
// include mesh
#include "mesh.h"
// include color
#include "color.h"
// include entity
#include "entity.h"
// include framebuffer
#include "framebuffer.h"
// include input
#include "input.h"
// include fontoader
#include "fontloader.h"
// include text
#include "text.h"
// include shader
#include "sprite.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	// renderer functions to render scene
	void renderScene(Scene* scene, Shader* shader2D, Shader* shader3D);

	// renderer functions to render 3D objects
	void render3D(Entity* mesh, Shader* shader, Scene* scene, glm::vec3 parentPosition);

	// renderer functions to render 2D objects
	void render2D(Entity* mesh, Shader* shader, Scene* scene, glm::vec3 parentPosition);

	// renderer function to render framebuffer
	void renderFramebuffer(FrameBuffer* framebuffer, Shader* shader);

	// renderer function to render text
	void renderText(Shader* shader, Text* text);
private:
	// font loader
	FontLoader* fontloader;

	// framebuffer quad
	Mesh* framebufferQuad;
};

#endif /* end renderer */
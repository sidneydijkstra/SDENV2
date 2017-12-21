/**
* @file renderer.h
*
* @brief The Renderer header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

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
// include shader
#include "resourcemanager.h"

/**
* @brief The Renderer class
*/
class Renderer
{
public:
	Renderer(); ///< @brief Constructor of the Renderer
	~Renderer(); ///< @brief Destructor of the Renderer

	/// @brief render a scene
	/// @param the scene you want to renderer
	/// @param the 2D shader
	/// @param the 3D shader
	/// @return void
	void renderScene(Scene* scene, Shader* shader2D, Shader* shader3D);
	/// @brief render a 3D entity
	/// @param the entity you want to render
	/// @param the shader you want to use
	/// @param the scene the entity is in
	/// @param the position of the parent
	/// @return void
	void render3D(Entity* mesh, Shader* shader, Scene* scene, glm::vec3 parentPosition);
	/// @brief render a 2D entity
	/// @param the entity you want to render
	/// @param the shader you want to use
	/// @param the scene the entity is in
	/// @param the position of the parent
	/// @return void
	void render2D(Entity* mesh, Shader* shader, Scene* scene, glm::vec3 parentPosition);
	/// @brief render a framebuffer
	/// @param the framebuffer you want to render
	/// @param the shader you want to use
	/// @return void
	void renderFramebuffer(FrameBuffer* framebuffer, Shader* shader);
	/// @brief render text
	/// @param the text you want to render
	/// @param the shader you want to use
	/// @return void
	void renderText(Text* text, Shader* shader);
private:
	FontLoader* _fontloader; ///< @brief the fontloader of the Renderer
	Mesh* framebufferQuad; ///< @brief the mesh for the framebuffers
	Resourcemanager* _resmanager; ///< @brief the resourcemanager of the Renderer
};

#endif /* end renderer */
/**
* @file framebuffer.h
*
* @brief The FrameBuffer header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "color.h"
#include "sdenv2config.h"

/**
* @brief The FrameBuffer class
*/
class FrameBuffer
{
public:
	FrameBuffer(); ///< @brief Constructor of the FrameBuffer
	~FrameBuffer(); ///< @brief Destructor of the FrameBuffer

	/// @brief create the FrameBuffer
	/// @return void
	void createFrameBuffer();
	/// @brief create the normal texture for the FrameBuffer
	/// @param the width of the texture
	/// @param the height of the texture
	/// @return void
	void createNormalTexture(int _width, int _height);
	/// @brief create the depth texture for the FrameBuffer
	/// @param the width of the texture
	/// @param the height of the texture
	/// @return void
	void createDepthTexture(int _width, int _height);

	/// @brief bind the FrameBuffer
	/// @return void
	void bind();
	/// @brief unbind the FrameBuffer
	/// @return void
	void unbind();

	/// @brief get the normal texture of the FrameBuffer
	/// @return int
	int getFrameBufferNormalTexture() { return _normalTexture; };
	/// @brief get the depth texture of the FrameBuffer
	/// @return int
	int getFrameBufferDepthTexture() { return _depthTexture; };

	/// @brief add a costum shader to the framebuffer
	/// @param the location of the vertex shader
	/// @param the location of the fragment shader
	/// @return void
	void addCostumShader(const char* vertLocation, const char* fragLocation);
	/// @brief get the shader of the FrameBuffer
	/// @return Shader*
	Shader* shader() { return _shader; };

	glm::vec3 position; ///< @brief the position of the FrameBuffer
	glm::vec3 rotation; ///< @brief the rotation of the FrameBuffer
	glm::vec3 size; ///< @brief the size of the FrameBuffer
	Color background; ///< @brief the background color of the FrameBuffer

private:

	// frame buffer
	unsigned int _framebuffer; ///< @brief the Framebuffer id
	unsigned int _rbo; ///< @brief the Framebuffer rbo
	
	// textures
	unsigned int _normalTexture; ///< @brief the normal texture of the framebuffer
	unsigned int _depthTexture; ///< @brief the depth texture of the framebuffer

	// shaders
	Shader* _shader; ///< @brief the shader of the framebuffer
	const GLchar* _vertShader; ///< @brief the vertex shader of the framebuffer
	const GLchar* _fragShader; ///< @brief the fragment shader of the framebuffer

};

#endif /* end framebuffer */
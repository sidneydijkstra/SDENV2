
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

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();
	// create the frame buffer
	void createFrameBuffer();
	// create normal texture atachment
	void createNormalTexture(int _width, int _height);
	// create depth texture atachment
	void createDepthTexture(int _width, int _height);
	// bind the frame buffer
	void bind();
	// unbind the frame buffer
	void unbind();
	// get frame buffer normal texture
	int getFrameBufferNormalTexture() { return _normalTexture; };
	// get frame buffer depth texture
	int getFrameBufferDepthTexture() { return _depthTexture; };

private:
	// frame buffer
	unsigned int _framebuffer;
	unsigned int _rbo;
	
	// textures
	unsigned int _normalTexture;
	unsigned int _depthTexture;
};

#endif /* end framebuffer */
#include "framebuffer.h"

// framebuffer constructor
FrameBuffer::FrameBuffer(){
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	//unsigned int _rbo;
	//glGenRenderbuffers(1, &_rbo);
	//glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height); // use a single renderbuffer object for both a depth AND stencil buffer.
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo); // now actually attach it

	this->createFrameBuffer();
	this->createNormalTexture(SWIDTH, SHEIGHT);

	// set shader
	_vertShader = "shaders/framebuffer.vert";
	_fragShader = "shaders/framebuffer.frag";
	_shader = new Shader(_vertShader, "", _fragShader);

	// set position size and backgroundcolor
	position = glm::vec3(SWIDTH / 2, SHEIGHT / 2, 0);
	rotation = glm::vec3(0,0,0);
	size = glm::vec3(100, 100, 0);

	// set render entitys to false
	_renderEntitys = false;
}

// framebuffer deconstructor
FrameBuffer::~FrameBuffer(){
	delete _shader;
}

void FrameBuffer::createFrameBuffer(){
	glGenFramebuffers(1, &_framebuffer);
}

void FrameBuffer::createNormalTexture(int _width, int _height){
	this->bind();

	// create texture
	glGenTextures(1, &_normalTexture);
	glBindTexture(GL_TEXTURE_2D, _normalTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// bind texture to frame buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _normalTexture, 0);

	// create render buffer
	glGenRenderbuffers(1, &_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);
	// check if framebuffer is good
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}

	this->unbind();
}

void FrameBuffer::createDepthTexture(int _width, int _height){
	this->bind();

	// create texture
	glGenTextures(1, &_depthTexture);
	glBindTexture(GL_TEXTURE_2D, _depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// bind texture to frame buffer
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _depthTexture, 0);
	//glDrawBuffer(GL_NONE);

	// create render buffer
	glGenRenderbuffers(1, &_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rbo);

	// check if framebuffer is good
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}

	this->unbind();
}

void FrameBuffer::bind(){
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
}

void FrameBuffer::unbind(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::addCostumShader(const char * vertLocation, const char * fragLocation){
	if (_shader != NULL) {
		delete _shader;
	}

	_vertShader = vertLocation;
	_fragShader = fragLocation;
	_shader = new Shader(_vertShader, "", _fragShader);
}

void FrameBuffer::addRenderEntity(Entity* e){
	_renderEntitys = true;
	_entitysToRender.clear();

	_entitysToRender.push_back(e);
}

void FrameBuffer::removeRenderEntitys(){
	_renderEntitys = false;
	_entitysToRender.clear();
}

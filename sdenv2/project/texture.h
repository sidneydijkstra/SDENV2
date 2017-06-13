
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <SOIL.h>

class Texture
{
public:
	Texture();
	GLuint loadNormalTexture(const char* location);
	GLuint loadCubeMapTexture(const char* right, const char* left, const char* top, const char* bottom, const char* back, const char* front);
private:
	
};

#endif /* end texture */
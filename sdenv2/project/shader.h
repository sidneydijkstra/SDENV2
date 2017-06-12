#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>; // Include glew to get all the required OpenGL headers

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	// The program ID
	GLuint program;
	// Use the program
	void use();
private :

};

#endif /* end shader */
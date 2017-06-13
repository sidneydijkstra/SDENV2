#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>; // Include glew to get all the required OpenGL headers

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	// The program ID
	GLuint program;
	// Use the program
	void use();

	// shader uniform functions
	void setMat4(const char * name, glm::mat4);
private :

};

#endif /* end shader */
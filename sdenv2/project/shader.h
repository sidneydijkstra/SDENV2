/**
* @file shader.h
*
* @brief The Shader header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>;

/**
* @brief The Shader class
*/
class Shader
{
public:
	/// @brief Constructor of the Shader
	/// @param the vertex Shader location
	/// @param the geometry Shader location
	/// @param the fragment Shader location
	Shader(const GLchar* vertexPath, const GLchar* geometryPath, const GLchar* fragmentPath);

	/// @brief use the current Shader program
	/// @return void
	void use();

	/// @brief set a glm::mat4 in the 
	/// @param the name of the variable in the Shader
	/// @param the value you want to set it to
	/// @return void
	void setMat4(const char* name, glm::mat4 value);
	/// @brief set a glm::vec3 in the 
	/// @param the name of the variable in the Shader
	/// @param the value you want to set it to
	/// @return void
	void setVec3(const char* name, glm::vec3 value);
	/// @brief set a float in the 
	/// @param the name of the variable in the Shader
	/// @param the value you want to set it to
	/// @return void
	void setFloat(const char* name, float value);
	/// @brief set a int in the 
	/// @param the name of the variable in the Shader
	/// @param the value you want to set it to
	/// @return void
	void setInt(const char * name, float value);
	/// @brief set a bool in the 
	/// @param the name of the variable in the Shader
	/// @param the value you want to set it to
	/// @return void
	void setBool(const char * name, bool value);
private:
	GLuint program; ///< @brief the current shader program

	/// @brief load a Shader file
	/// @param the file location
	/// @return std::string
	std::string loadShaderFile(const GLchar* path);

	/// @brief create a Shader
	/// @param the Shader type
	/// @param the Shader source
	/// @param the Shader name
	/// @return GLuint
	GLuint createShader(GLenum type, const GLchar* source, std::string name);

	/// @brief load a Shader program
	/// @return void
	void loadShaderProgram();
};

#endif /* end shader */
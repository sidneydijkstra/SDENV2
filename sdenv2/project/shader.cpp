
#include "shader.h"

// shader constructor
Shader::Shader(const GLchar* vertexPath, const GLchar* geometryPath, const GLchar* fragmentPath) {
	// set shader program
	this->program = glCreateProgram();

	// set vertexshader
	std::string vertexSourcePointer = loadShaderFile(vertexPath);
	const char* vertexSourch = vertexSourcePointer.c_str();
	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexSourch, "vertex shader");
	glAttachShader(this->program, vertexShader);

	// set geometryshader
	std::string geometrySourcePointer = loadShaderFile(geometryPath);
	if (geometrySourcePointer.compare("") != 0) {
		const char* geometrySourch = geometrySourcePointer.c_str();
		GLuint geometryShader = createShader(GL_VERTEX_SHADER, geometrySourch, "geometry shader");
		glAttachShader(this->program, geometryShader);
	}

	// set fragmentshader
	std::string fragmentSourcePointer = loadShaderFile(fragmentPath);
	const char* fragmentSourch = fragmentSourcePointer.c_str();
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentSourch, "fragment shader");
	glAttachShader(this->program, fragmentShader);


	// attach shaders
	glLinkProgram(this->program);

	// load shader program
	loadShaderProgram();

	// delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// use shader
void Shader::use() {
	glUseProgram(this->program);
}

// load shader file
std::string Shader::loadShaderFile(const GLchar * path){
	std::string shaderCode;
	std::ifstream shaderStream(path);
	if (shaderStream.is_open()) {
		std::string Line = "";
		while (getline(shaderStream, Line)) {
			shaderCode += "\n" + Line;
		}
		shaderStream.close();
	}else {
		shaderCode = "";
	}
	return shaderCode;
}

GLuint Shader::createShader(GLenum type, const GLchar* source, std::string name){
	// error info
	GLint success;
	GLchar infoLog[512];

	// create shader
	GLuint shader;
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	// check if succes on loading shader
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR IN: " << name << "\n" << infoLog << std::endl;
	}else {
		std::cout << "loaded: '" << name << "'" << std::endl;
	}

	return shader;
}

void Shader::loadShaderProgram(){
	// error info
	GLint success;
	GLchar infoLog[512];
	// load program
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED [" << infoLog << "]" << std::endl;
	}
	else {
		std::cout << "loaded: 'shaderProgram'" << std::endl;
	}
}

// set mat4 in shader
void Shader::setMat4(const char* name, glm::mat4 value) {
	GLint uniform = glGetUniformLocation(this->program, name);
	glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
}

// set vec3 in shader
void Shader::setVec3(const char* name, glm::vec3 value) {
	GLint uniform = glGetUniformLocation(this->program, name);
	glUniform3f(uniform, value.x, value.y, value.z);
}

// set float in shader
void Shader::setFloat(const char * name, float value){
	GLint uniform = glGetUniformLocation(this->program, name);
	glUniform1f(uniform, value);
}

// set int in shader
void Shader::setInt(const char * name, float value) {
	GLint uniform = glGetUniformLocation(this->program, name);
	glUniform1d(uniform, value);
}

// set bool in shader
void Shader::setBool(const char * name, bool value) {
	GLint uniform = glGetUniformLocation(this->program, name);
	glUniform1d(uniform, value);
}

#ifndef MESH_H
#define MESH_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	// mesh variabels
	glm::vec3 position = glm::vec3(0,0,0);		// mesh position
	glm::vec3 scale = glm::vec3(1, 1, 1);		// mesh scale 
	glm::vec3 rotation = glm::vec3(0, 0, 0);	// mesh rotation

	// init 3D cube buffer
	void initCubeBuffer();
	GLuint _VAO, _VBO;

	// load mesh texture
	void loadMeshTexture(const char* location);
	GLuint _normalTexture;
private:
	Texture* _textureLoader;
};

#endif /* end mesh */
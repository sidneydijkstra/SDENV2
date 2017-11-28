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
#include "color.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	// mesh variabels
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	// mesh color
	Color color;

	// mesh buffer varables
	GLuint _VAO, _VBO;
	int _drawsize = 36;

	// load 3d cube
	void loadCube();

	// load 2d quad
	void loadQuad();

	// load 3d object
	void loadObject(const char * location);

	// load mesh textures
	void loadMeshTexture(const char* location);

	// mesh textures
	GLuint _normalTexture;
private:
	Texture _textureLoader;
};

#endif /* end mesh */
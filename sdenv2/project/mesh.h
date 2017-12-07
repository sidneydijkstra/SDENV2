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

#include "sprite.h"
#include "spriteanimator.h"
#include "color.h"
#include "sdenv2config.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	// mesh buffer varables
	GLuint _VAO, _VBO;
	int _drawsize;

	// load 3d cube
	void loadCube();

	// load 3d object
	void loadObject(const char * location);

	// load 2d quad
	void loadQuad();
private:
};

#endif /* end mesh */
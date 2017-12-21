/**
* @file mesh.h
*
* @brief The Mesh header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

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

/**
* @brief The Mesh class
*/
class Mesh
{
public:
	Mesh(); ///< @brief Constructor of the Mesh
	~Mesh(); ///< @brief Destructor of the Mesh

	// mesh buffer varables
	GLuint _VAO; ///< @brief the VAO buffer of Mesh
	GLuint _VBO; ///< @brief the VBO buffer of Mesh
	int _drawsize; ///< @brief the drawsize of Mesh

	/// @brief load the Mesh for a cube
	/// @return void
	void loadCube();
	/// @brief load the Mesh for a quad
	/// @return void
	void loadQuad();
	/// @brief load the Mesh for a object with a .obj file
	/// @param the file location
	/// @return void
	void loadObject(const char * location);
private:
};

#endif /* end mesh */
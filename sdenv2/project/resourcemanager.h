/**
* @file resourcemanager.h
*
* @brief The Resourcemanager header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <sstream>
#include <iostream>
#include <map>

// include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// include glew
#include <GL/glew.h>
// include soil
#include <SOIL.h>

#include "texture.h"

/**
* @brief The Resourcemanager class
*/
class Resourcemanager
{
public:
	Resourcemanager(); ///< @brief Constructor of the Resourcemanager
	~Resourcemanager(); ///< @brief Destructor of the Resourcemanager

	/// @brief get a texture
	/// @param the location of the texture
	/// @param the filter type
	/// @param the wrap type
	/// @return GLuint
	GLuint getTexture(const char* location, int filter, int wrap);

private:
	std::map<std::string, Texture*> _textures; ///< @brief the map of already loaded texures
};

#endif /* end RESOURCEMANAGER_H */

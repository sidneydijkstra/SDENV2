/**
* @file texture.h
*
* @brief The Texture header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <sstream>
#include <iostream>

// include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// include glew
#include <GL/glew.h>
// include soil
#include <SOIL.h>

/**
* @brief The Texture class
*/
class Texture
{
public:
	Texture(); ///< @brief Constructor of the Texture
	virtual ~Texture(); ///< @brief Destructor of the Texture

	/// @brief load a texture
	/// @param the location of the texture
	/// @param the filter type
	/// @param the wrap type
	/// @return void
	void loadTexture(const char* location, int filter, int wrap);
	/// @brief get the texture
	/// @return GLuint
	GLuint getTexture() { return _texture; };

private:
	GLuint _texture; ///< @brief the loaded texture
	 
	int _filter; ///< @brief the filter type
	int _wrap; ///< @brief the wrap type
};

#endif /* end TEXTURE_H */

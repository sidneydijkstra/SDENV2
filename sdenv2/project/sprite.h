/**
* @file sprite.h
*
* @brief The Sprite header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

// include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// include glew
#include <GL/glew.h>
// include soil
#include <SOIL.h>

/**
* @brief The Sprite class
*/
class Sprite
{
public:
	Sprite(); ///< @brief Constructor of the Sprite
	virtual ~Sprite(); ///< @brief Destructor of the Sprite

	/// @brief load a texture
	/// @param the loaction
	/// @param the filter type
	/// @param the wrap type
	/// @return void
	void loadTexture(const char* location, int filter, int wrap);
	/// @brief load a texture
	/// @param the loaction
	/// @return void
	void loadTexture(const char* location);
	/// @brief remove a texture
	/// @return void
	void removeTexture();

	/// @brief get the texture location
	/// @return const char*
	const char* texture() { return _texturename; };
	/// @brief get the filter type
	/// @return int
	int filter() { return _filter; }
	/// @brief get the wrap type
	/// @return int
	int wraping() { return _wrap; }
private:
	const char* _texturename; ///< @brief the location of the texture

	int _filter; ///< @brief the filter type
	int _wrap; ///< @brief the wrap type
};

#endif /* end SPRITE_H */

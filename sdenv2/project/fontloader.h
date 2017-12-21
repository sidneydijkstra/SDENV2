/**
* @file fontloader.h
*
* @brief The FontLoader header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef FONTLOADER_H
#define FONTLOADER_H

#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// include freetype
#include <ft2build.h>
#include FT_FREETYPE_H  

/**
* @brief The Character struct
*/
struct Character {
	GLuint textureID; ///< @brief the id of the glyph texture
	glm::ivec2 size; ///< @brief the size of the glyph
	glm::ivec2 bearing; ///< @brief the offset from baseline to left/top of glyph
	GLuint advance; ///< @brief the offset to advance to next glyph
};

/**
* @brief The FontLoader class
*/
class FontLoader
{
public:
	FontLoader(); ///< @brief Constructor of the FontLoader
	~FontLoader(); ///< @brief Destructor of the FontLoader

	/// @brief add a new font
	/// @param the file location
	/// @return void
	void addFont(const char* location);

	/// @brief get a font
	/// @param the file location
	/// @return std::map<GLchar, Character>
	std::map<GLchar, Character> getFont(const char* location);

private:
	std::map<std::string, std::map<GLchar, Character>> fonts; ///< @brief the fonts that are loaded
	std::vector<const char*> unknown; ///< @brief the fonts that cant be loaded
};

#endif /* end FONTLOADER_H */
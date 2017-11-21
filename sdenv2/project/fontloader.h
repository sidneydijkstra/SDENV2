
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

struct Character {
	GLuint     textureID;  // ID handle of the glyph texture
	glm::ivec2 size;       // Size of glyph
	glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
	GLuint     advance;    // Offset to advance to next glyph
};

class FontLoader
{
public:
	FontLoader();
	~FontLoader();

	// add a new font
	void addFont(const char* location);

	// get font if font not loaded get normal font
	std::map<GLchar, Character> getFont(const char* location);

private:
	std::map<std::string, std::map<GLchar, Character>> fonts;
	std::vector<const char*> unknown;
};

#endif /* end FONTLOADER_H */
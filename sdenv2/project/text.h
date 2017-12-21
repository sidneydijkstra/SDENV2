/**
* @file text.h
*
* @brief The Text header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <sstream>
#include <iostream>
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
* @brief The Text class
*/
class Text
{
public:
	///< @brief Constructor of the Text
	/// @param the font you want to use
	/// @param the scale of the text
	/// @param the color of the text
	Text(const char* font, float _scale, glm::vec3 _color = glm::vec3(1, 1, 1));
	~Text(); ///< @brief Destructor of the Text

	/// @brief set the font
	/// @param the location of the font
	/// @return void
	void setFont(const char* font);
	/// @brief get the current font
	/// @return const char*
	const char* getFont() { return _font; };

	/// @brief set color lerp
	/// @param the lerp start color
	/// @param the lerp end color
	/// @return void
	void setColorLerp(glm::vec3 s, glm::vec3 e);
	/// @brief remove the lerp
	/// @return void
	void removeColorLerp();
	/// @brief get if lerp is active
	/// @return bool
	bool doColorLerp();
	/// @brief get the lerp color
	/// @param the index
	/// @return glm::vec3
	glm::vec3 getColorLerp(int i);

	float scale; ///< @brief the scale of the Text
	glm::vec3 color; ///< @brief the color of the Text
	std::string message; ///< @brief the message of the Text
	glm::vec3 position; ///< @brief the position of the Text

	GLuint _VAO; ///< @brief the VAO of the Text
	GLuint _VBO; ///< @brief the VBO of the Text
private:
	std::vector<glm::vec3> _lerpColors; ///< @brief the list of lerp colors
	const char* _font; ///< @brief the font of the text

	/// @brief initialized the text
	/// @return void
	void init();
};

#endif /* end TEXT_H */
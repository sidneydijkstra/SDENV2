
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

class Text
{
public:
	Text(const char* font, float _scale, glm::vec3 _color = glm::vec3(1, 1, 1));
	~Text();

	// load new font
	void setFont(const char* font);
	const char* getFont() { return _font; };

	// color options
	void setColorLerp(glm::vec3 s, glm::vec3 e);
	void removeColorLerp();
	bool doColorLerp();
	glm::vec3 getColorLerp(int i);

	// text size
	float scale;
	// text color
	glm::vec3 color;
	// text message
	std::string message;
	// text position
	glm::vec3 position;

	// VAO and VBO
	GLuint _VAO, _VBO;
private:
	// color lerp vars
	std::vector<glm::vec3> _lerpColors;

	// text font
	const char* _font;
	// init text
	void init();
};

#endif /* end TEXT_H */

#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Color
{
public:
	Color(int _r = 0, int _g = 0, int _b = 0);
	~Color();

	// set color
	void setColor(int _r, int _g, int _b);
	void setColor(glm::vec3 _c);

	// get color in glsl format
	glm::vec3 getColor();

	// lerp color
	Color lerpColor(Color c1, Color c2, float amount);

	// RGB color
	short int r;
	short int g;
	short int b;
private:

};

#endif /* end COLOR_H */
#include "color.h"

Color::Color(int _r, int _g, int _b){
	r = _r;
	g = _g;
	b = _b;
}

Color::~Color()
{
}

void Color::setColor(int _r, int _g, int _b){
	r = _r;
	g = _g;
	b = _b;
}

void Color::setColor(glm::vec3 _c){
	r = _c.x;
	g = _c.y;
	b = _c.z;
}

glm::vec3 Color::getColor(){
	float i = 1.0f / 255.0f;
	return glm::vec3(i * r, i * g, i * b);
}

Color Color::lerpColor(Color c1, Color c2, float amount){
	if (amount < 0) { amount = 0; }
	if (amount > 1) { amount = 1; }

	uint8_t r = floor(c1.r + (c2.r - c1.r)*amount);
	uint8_t g = floor(c1.g + (c2.g - c1.g)*amount);
	uint8_t b = floor(c1.b + (c2.b - c1.b)*amount);

	return Color(r,g,b);
}

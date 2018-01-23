#include "ui/uitext.h"

UIText::UIText(const char* font, float _scale, glm::vec3 _color) {
	this->setFont(font);
	this->scale = _scale;
	this->color = _color;

	this->message = "NULL";
	this->_lerpColors = std::vector<glm::vec3>();

	this->init();
}

UIText::~UIText() {
}

void UIText::setFont(const char* font) {
	_font = font;
}

void UIText::setColorLerp(glm::vec3 s, glm::vec3 e) {
	_lerpColors.clear();

	int l = message.length();

	float r = (s.x - e.x) / l;
	float g = (s.y - e.y) / l;
	float b = (s.z - e.z) / l;

	for (int i = 1; i <= l; i++) {
		glm::vec3 c = glm::vec3(s.x - r * i, s.y - g * i, s.z - b * i);
		_lerpColors.push_back(c);
	}
	_lerpColors.push_back(e);
}

void UIText::removeColorLerp() {
	_lerpColors.clear();
}

bool UIText::doColorLerp() {
	if (_lerpColors.size() > 0) {
		return true;
	}
	return false;
}

glm::vec3 UIText::getColorLerp(int i) {
	if (i < 0 || i >= _lerpColors.size()) {
		return glm::vec3(0, 1, 0);
	}
	return _lerpColors[i];
}

void UIText::init() {
	// create text quad
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
#include "tile.h"

Tile::Tile(int _x, int _y, int _w, int _h) {
	this->mesh()->loadQuad();
	this->position = glm::vec3(_x, _y, 0);
	this->size = glm::vec3(_w, _h, 0);
	this->color = Color(rand() % 255, rand() % 255, rand() % 255);
}

Tile::~Tile() {
}

void Tile::update(float deltatime) {
}
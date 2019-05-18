#include "tile.h"

Tile::Tile(int _x, int _y, int _w, int _h) {
	this->mesh()->loadQuad();
	this->position = glm::vec3(_x, _y, 0);
	this->size = glm::vec3(_w, _h, 0);

	this->sprite()->loadTexture(rand() & 2 == 1 ? "assets/tile_3.png" : rand() % 2 == 1 ? "assets/tile_1.png" : "assets/tile_2.png");
}

Tile::~Tile() {
}

void Tile::update(float deltatime) {
}
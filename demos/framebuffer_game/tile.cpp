#include "tile.h"

Tile::Tile(glm::vec3 _position, glm::vec3 _scale, const char* _texture){
	this->mesh()->loadQuad();
	this->position = _position;
	this->scale = _scale;
	this->sprite()->loadTexture(_texture, 0, 0);

	this->color = Color(255,255,255);

	this->setOffset(4);
}

Tile::~Tile(){
}

void Tile::update(float deltatime){
}

#include "tile.h"

Tile::Tile(glm::vec3 _position, glm::vec3 _scale, const char* _texture){
	this->mesh()->loadQuad();
	this->position = _position;
	this->scale = _scale;
	this->sprite()->loadTexture(_texture, 0, 0);

	this->color = Color(255,255,255);
}

Tile::~Tile(){
}

void Tile::update(float deltatime){
}

bool Tile::collision(Entity * e){

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (tPos.x + tSize.x > ePos.x - eSize.x && tPos.x - tSize.x < ePos.x + eSize.x && tPos.y + tSize.y > ePos.y - eSize.y && tPos.y - tSize.y < ePos.y + eSize.y ){
		return true;
	}

	return false;
}

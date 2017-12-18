#include "tile.h"

Tile::Tile(glm::vec3 _position, glm::vec3 _scale, const char* _texture){
	this->mesh()->loadQuad();
	this->position = _position;
	this->scale = _scale;
	this->sprite()->loadTexture(_texture, 0, 0);

	this->color = Color(255,255,255);

	_offset = 4;
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

bool Tile::topCollision(Entity * e){

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (this->collision(e) && ePos.y - eSize.y > tPos.y + (tSize.y - _offset)) {
		return true;
	}
	return false;
}

bool Tile::bottomCollision(Entity * e){

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (this->collision(e) && ePos.y + eSize.y < tPos.y - (tSize.y - _offset)) {
		return true;
	}
	return false;
}

bool Tile::leftCollision(Entity * e){

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (this->collision(e) && ePos.x + eSize.x < tPos.x - (tSize.x - 1)) {
		return true;
	}

	return false;
}

bool Tile::rightCollision(Entity * e){

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (this->collision(e) && ePos.x - eSize.x > tPos.x + (tSize.x - 1)) {
		return true;
	}

	return false;
}

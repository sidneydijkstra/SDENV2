#include "collider.h"

Collider::Collider()
{
}

Collider::~Collider()
{
}

bool Collider::collision(Entity * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (tPos.x + tSize.x > ePos.x - eSize.x && tPos.x - tSize.x < ePos.x + eSize.x && tPos.y + tSize.y > ePos.y - eSize.y && tPos.y - tSize.y < ePos.y + eSize.y) {
		return true;
	}

	return false;
}

bool Collider::topCollision(Entity * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (this->collision(e) && ePos.y - eSize.y > tPos.y + (tSize.y - _offset)) {
		return true;
	}
	return false;
}

bool Collider::bottomCollision(Entity * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (this->collision(e) && ePos.y + eSize.y < tPos.y - (tSize.y - _offset)) {
		return true;
	}
	return false;
}

bool Collider::leftCollision(Entity * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (this->collision(e) && ePos.x + eSize.x < tPos.x - (tSize.x - 1)) {
		return true;
	}

	return false;
}

bool Collider::rightCollision(Entity * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (this->collision(e) && ePos.x - eSize.x > tPos.x + (tSize.x - 1)) {
		return true;
	}

	return false;
}


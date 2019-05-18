#pragma once

#ifndef COLLISION_H
#define COLLISION_H

#include <entity.h>

class Collision: public Entity
{
public:
	Collision();
	virtual ~Collision();

	virtual void update(float deltatime);

	void collide(Collision* _col);
	glm::vec3 getPointToBoarder(Collision* _col); 
	glm::vec3 getBoarderPlacementPoint(Collision* _col);
	bool isColliding(Collision* _col);

	// check collision
	bool collision(Collision* e);
	// check top collision
	bool topCollision(Collision* e);
	// check bottom collision
	bool bottomCollision(Collision* e);
	// check left collision
	bool leftCollision(Collision* e);
	// check right collision
	bool rightCollision(Collision* e);

	bool _isStatic;
private:


	
	
};

#endif /* end COLLISION_H */

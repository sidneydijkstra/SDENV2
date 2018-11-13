
#ifndef COLLIDER_H
#define COLLIDER_H

#include <entity.h>

class Collider : public Entity
{
public:
	Collider();
	~Collider();

	// set offset
	void setOffset(int value) { _offset = value; };

	// check collision
	bool collision(Entity* e);
	// check top collision
	bool topCollision(Entity* e);
	// check bottom collision
	bool bottomCollision(Entity* e);
	// check left collision
	bool leftCollision(Entity* e);
	// check right collision
	bool rightCollision(Entity* e);

private:
	int _offset;
};

#endif /* end COLLIDER_H */
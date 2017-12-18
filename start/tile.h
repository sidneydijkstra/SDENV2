
#ifndef TILE_H
#define TILE_H

#include <entity.h>

class Tile : public Entity
{
public:
	Tile(glm::vec3 _position, glm::vec3 _scale, const char* _texture);
	~Tile();

	void update(float deltatime);

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

#endif /* end TILE_H */

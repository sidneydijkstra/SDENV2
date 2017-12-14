
#ifndef TILE_H
#define TILE_H

#include <entity.h>

class Tile : public Entity
{
public:
	Tile(glm::vec3 _position, glm::vec3 _scale, const char* _texture);
	~Tile();

	void update(float deltatime);

	bool collision(Entity* e);

	bool topCollision(Entity* e);
	bool bottomCollision(Entity* e);
	bool leftCollision(Entity* e);
	bool rightCollision(Entity* e);

private:
	int _offset;
};

#endif /* end TILE_H */

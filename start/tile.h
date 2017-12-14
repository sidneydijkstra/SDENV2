
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

private:
};

#endif /* end TILE_H */


#ifndef TILE_H
#define TILE_H

#include "collider.h"

class Tile : public Collider
{
public:
	Tile(glm::vec3 _position, glm::vec3 _scale, const char* _texture);
	~Tile();

	void update(float deltatime);

private:
};

#endif /* end TILE_H */

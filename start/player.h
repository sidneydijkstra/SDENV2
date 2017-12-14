
#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>
#include "tile.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void update(float deltatime, Tile* t);

private:
	glm::vec3 velocity;
	glm::vec3 acceleration;
};

#endif /* end PLAYER_H */

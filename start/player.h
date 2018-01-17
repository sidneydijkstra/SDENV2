
#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>
#include "tile.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void update(float deltatime, std::vector<Tile*> t);

	void addForce(glm::vec3 _force);

private:
	glm::vec3 velocity;
	glm::vec3 acceleration;
};

#endif /* end PLAYER_H */

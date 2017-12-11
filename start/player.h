
#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>

class Player : public Entity
{
public:
	Player();
	~Player();

	void update(float deltatime);

private:
	glm::vec3 vel;
};

#endif /* end PLAYER_H */

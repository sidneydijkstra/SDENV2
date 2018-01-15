
#ifndef COIN_H
#define COIN_H

#include "collider.h"

class Coin : public Collider
{
public:
	Coin(glm::vec3 _position);
	~Coin();

	void update(float deltatime);

private:
};

#endif /* end COIN_H */
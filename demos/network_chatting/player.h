#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>

class Player : public Entity
{
public:
	Player();
	virtual ~Player();

	void update(float deltatime);

	int networkID;
private:
	float _moveSpeed;
};

#endif /* end PLAYER_H */

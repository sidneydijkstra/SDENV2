#pragma once

#ifndef ENEMY_H
#define ENEMY_H


#include <entity.h>
#include <mesh.h>
#include "player.h"
#include "tile.h"

class Enemy : public Entity
{
public:
	Enemy(Player* target);
	virtual ~Enemy();

	virtual void update(float deltatime);

private:
	Player* _target;
};

#endif /* end ENEMY_H */

#pragma once

#ifndef ENEMY_H
#define ENEMY_H


#include <entity.h>
#include <string>
#include <mesh.h>
#include "player.h"
#include "tile.h"

class Enemy : public Entity
{
public:
	Enemy(Player* target, float minx, float maxxs);
	virtual ~Enemy();

	virtual void update(float deltatime, std::vector<Tile*> t);

private:
	// target of enemy
	Player* _target;

	// velocity of enemy
	glm::vec3 _velocity;
	glm::vec3 _acceleration;

	// min and max x enemy can walk
	float _minx;
	float _maxx;
};

#endif /* end ENEMY_H */

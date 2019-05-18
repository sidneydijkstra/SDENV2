#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include <entity.h>
#include <mesh.h>
#include "collision.h"


class Object : public Collision
{
public:
	Object();
	virtual ~Object();

	virtual void update(float deltatime);

	glm::vec3 vel;
	glm::vec3 acc;
	float speed;
	float limit;
private:
};

#endif /* end OBJECT_H */

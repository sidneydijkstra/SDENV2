
#ifndef ROCKET_H
#define ROCKET_H

#include <entity.h>

class Rocket : public Entity
{
public:
	Rocket();
	~Rocket();

	void update(float deltatime);

	void addForce(glm::vec3 force);

private:
	std::vector<glm::vec3> movement;
	int _current;

	glm::vec3 vel;
	glm::vec3 acc;
};

#endif /* end ROCKET_H */

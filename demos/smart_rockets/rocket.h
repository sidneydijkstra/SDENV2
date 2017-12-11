
#ifndef ROCKET_H
#define ROCKET_H

#include <entity.h>

class Rocket : public Entity
{
public:
	Rocket();
	~Rocket();

	void update(float deltatime);

	void reload();

private:
	std::vector<glm::vec3> movement;
	int _current;
};

#endif /* end ROCKET_H */

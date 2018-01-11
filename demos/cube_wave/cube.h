
#ifndef ROCKET_H
#define ROCKET_H

#include <entity.h>

class Cube : public Entity
{
public:
	Cube();
	~Cube();

	void update(float deltatime);
private:
};

#endif /* end ROCKET_H */


#ifndef MYENTITY_H
#define MYENTITY_H

#include "../sdenv2/project/mesh.h"
#include "../sdenv2/project/sdenv2config.h"

class MyEntity : public Mesh
{
public:
	MyEntity();
	~MyEntity();

	void update(float deltatime);

private:
	glm::vec3 vel;
	glm::vec3 acc;
};

#endif /* end MYENTITY_H */

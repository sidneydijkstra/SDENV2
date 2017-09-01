
#ifndef PARTICALSYSTEM_H
#define PARTICALSYSTEM_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "partical.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ParticalSystem
{
public:
	ParticalSystem();
	~ParticalSystem();

	void update(float deltatime);

	std::vector<Mesh*> getAllParticalsMesh();

	glm::vec3 position;

private:
	// list of particals
	std::vector<Partical*> _particals;

	// last spawn partical time
	float _lastSpawnedTime;
};

#endif /* end ParticalSystem */
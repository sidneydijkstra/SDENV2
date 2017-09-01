
#ifndef PARTICAL_H
#define PARTICAL_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "mesh.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Partical
{
public:
	Partical(float lifetime);
	~Partical();

	void update(float deltatime);

	// get mesh
	Mesh* getMesh() { return _mesh; };
	// get lifetime
	float getLifeTime() { return _lifetime; };

	// partical velocity
	glm::vec3 velocity;

private:
	// partical its mesh
	Mesh* _mesh;

	// particals variables
	float _lifetime;

	// vel over lifetime
	glm::vec3 velOverLifeStart;
	glm::vec3 velOverLifeEnd;
	float velOverLifeSlerp;
};

#endif /* end ParticalSystem */
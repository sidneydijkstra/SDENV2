
#ifndef LIGHT_H
#define LIGHT_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
public:
	Light();
	~Light();

	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 lightColor = glm::vec3(1, 1, 1);
	float ambientStrength = 0.15f;
	float specularStrength = 0.5f;

private:

};

#endif /* end light */
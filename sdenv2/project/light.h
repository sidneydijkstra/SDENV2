/**
* @file light.h
*
* @brief The Light header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef LIGHT_H
#define LIGHT_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
* @brief The Entity class
*/
class Light
{
public:
	Light(); ///< @brief Constructor of the Light
	~Light(); ///< @brief Destructor of the Light

	glm::vec3 position = glm::vec3(0, 0, 0); ///< @brief the position of the Light
	glm::vec3 lightColor = glm::vec3(1, 1, 1); ///< @brief the color of the Light
	float ambientStrength = 0.15f; ///< @brief the ambient strength of the Light
	float specularStrength = 0.5f; ///< @brief the specular strength of the Light

private:

};

#endif /* end light */
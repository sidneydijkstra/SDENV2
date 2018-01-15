/**
* @file line.h
*
* @brief The Line header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef TIMER_H
#define LINE_H

#include <iostream>
#include <vector>

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
* @brief The Line class
*/
class Line
{
public:
	Line(); ///< @brief Constructor of the Timer
	~Line(); ///< @brief Destructor of the Timer

	void addPoint(glm::vec3 point);
	std::vector<glm::vec3> getPoints();

private:
	std::vector<glm::vec3> _points;
};

#endif /* end TIMER_H */
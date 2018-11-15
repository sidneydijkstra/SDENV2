/**
* @file line.h
*
* @brief The Line header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef LINE_H
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
	Line(); ///< @brief Constructor of the Line
	~Line(); ///< @brief Destructor of the Line

	void addPoint(glm::vec3 point);
	std::vector<glm::vec3> getPoints();

private:
	std::vector<glm::vec3> _points;
};

#endif /* end LINE_H */
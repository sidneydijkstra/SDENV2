
#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

// include glew and glfw3
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "input.h"

class Camera
{
public:
	Camera();

	void move(float deltaTime) { cameraMouseMovement(deltaTime); cameraPositionMovement(deltaTime); };
	// Camera
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

	GLfloat yaw = -90.0f;
	GLfloat pitch = 0.0f;
	GLfloat fov = 70.0f;
	GLfloat lastX;
	GLfloat lastY;
private:
	// camera move
	void cameraPositionMovement(float deltaTime);
	void cameraMouseMovement(float deltaTime);
};

#endif
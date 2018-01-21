
/**
* @file camera.h
*
* @brief The Camera header file.
*
* 
*
*/
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
#include "sdenv2config.h"

/**
* @brief The Camera class
*/
class Camera
{
public:
	Camera(); ///< @brief Constructor of the Camera

	/// @brief the move function of the camera
	/// @param the deltatime
	/// @return void
	void move(float deltaTime) { cameraMouseMovement(deltaTime); cameraPositionMovement(deltaTime); };
	
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); ///< @brief the position of the camera
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f); ///< @brief the front of the camera
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); ///< @brief the up of the camera
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f); ///< @brief the right of the camera

	GLfloat yaw = -90.0f; ///< @brief the yaw of the camera
	GLfloat pitch = 0.0f; ///< @brief the pitch of the camera
	GLfloat fov = 70.0f; ///< @brief the fov of the camera

	// temp function
	void updateCameraVector(){
		glm::vec3 front;
		front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		front.y = sin(glm::radians(this->pitch));
		front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

		this->front = glm::normalize(front);

		this->right = glm::normalize(glm::cross(this->front, glm::vec3(0.0f, 1.0f, 0.0f)));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}
private:
	/// @brief the position movement function of the camera
	/// @param the deltatime
	/// @return void
	void cameraPositionMovement(float deltaTime);
	/// @brief the mouse movement function of the camera
	/// @param the deltatime
	/// @return void
	void cameraMouseMovement(float deltaTime);

	GLfloat lastX; ///< @brief the lastX of the camera
	GLfloat lastY; ///< @brief the lastY of the camera
};

#endif
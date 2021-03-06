
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

	/// @brief the move3D function of the camera in 3D space
	/// @param the deltatime
	/// @return void
	void move3D(float deltaTime) { cameraMouseMovement(deltaTime); cameraPositionMovement(deltaTime); };
	/// @brief the move2D function of the camera in 2D space
	/// @param the deltatime
	/// @param the move speed
	/// @return void
	void move2D(float deltaTime, float speed);
	
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); ///< @brief the position of the camera
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f); ///< @brief the front of the camera
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); ///< @brief the up of the camera
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f); ///< @brief the right of the camera

	GLfloat yaw = -90.0f; ///< @brief the yaw of the camera
	GLfloat pitch = 0.0f; ///< @brief the pitch of the camera
	GLfloat fov = 70.0f; ///< @brief the fov of the camera
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
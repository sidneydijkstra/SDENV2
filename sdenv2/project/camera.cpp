
#include "camera.h"

Camera::Camera() {
	this->lastX = 800 / 2.0;
	this->lastY = 600 / 2.0;
}

void Camera::cameraPositionMovement(float deltaTime, Input* input) {
	// Camera controls
	GLfloat cameraSpeed = 5.0f * deltaTime;
	if (input->getKey(GLFW_KEY_W))
		this->position += cameraSpeed * this->front;
	if (input->getKey(GLFW_KEY_S))
		this->position -= cameraSpeed * this->front;
	if (input->getKey(GLFW_KEY_A))
		this->position -= glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
	if (input->getKey(GLFW_KEY_D))
		this->position += glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
	if (input->getKey(GLFW_KEY_SPACE))
		this->position += cameraSpeed * this->up;
	if (input->getKey(GLFW_KEY_LEFT_SHIFT))
		this->position -= cameraSpeed * this->up;
}

bool firstMouse = true;
void Camera::cameraMouseMovement(float deltaTime, Input* input) {
	float xpos = input->getMouseX();
	float ypos = input->getMouseY();
	if (firstMouse) {
		this->lastX = xpos;
		this->lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - this->lastX;
	GLfloat yoffset = this->lastY - ypos; // Reversed since y-coordinates go from bottom to left
	this->lastX = xpos;
	this->lastY = ypos;

	GLfloat sensitivity = 0.05;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(front);
}
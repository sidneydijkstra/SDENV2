
#include "camera.h"


Camera::Camera() {
	this->lastX = 1000 / 2.0;
	this->lastY = 800 / 2.0;

	//this->position = glm::vec3(SWIDTH / 2, SHEIGHT / 2, 0);
	//this->position.z = 630;

	this->yaw = 0.0f;
	this->pitch = 0.0f;

	std::cout << "made a camera" << std::endl;
}

void Camera::move2D(float deltaTime, float speed) {
	// Camera controls
	if (Input::getKey(GLFW_KEY_A)) {
		this->position.x -= speed * deltaTime;
	}else
	if (Input::getKey(GLFW_KEY_D)) {
		this->position.x += speed * deltaTime;
	}
	if (Input::getKey(GLFW_KEY_W)) {
		this->position.y += speed * deltaTime;
	}else
	if (Input::getKey(GLFW_KEY_S)) {
		this->position.y -= speed * deltaTime;
	}
}

void Camera::cameraPositionMovement(float deltaTime) {
	// Camera controls
	GLfloat cameraSpeed = 5.0f * deltaTime;
	if (Input::getKey(GLFW_KEY_W))
		this->position += cameraSpeed * this->front;
	if (Input::getKey(GLFW_KEY_S))
		this->position -= cameraSpeed * this->front;
	if (Input::getKey(GLFW_KEY_A))
		this->position -= glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
	if (Input::getKey(GLFW_KEY_D))
		this->position += glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
	if (Input::getKey(GLFW_KEY_SPACE))
		this->position += cameraSpeed * this->up;
	if (Input::getKey(GLFW_KEY_LEFT_SHIFT))
		this->position -= cameraSpeed * this->up;
}

bool firstMouse = true;
void Camera::cameraMouseMovement(float deltaTime) {
	float xpos = Input::getMouseX();
	float ypos = Input::getMouseY();

	//std::cout << "xpos: " << xpos << " ypos: " << ypos << std::endl;

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

	//std::cout << "yaw: " << this->yaw << " pitch: " << this->pitch << std::endl;
}
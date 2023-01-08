#include "../headers/Camera.h"

//constructor for camera class
Camera::Camera() {
	//define initial camera positions
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

//this function moves the camera up
void Camera::cameraRaise(const float cameraSpeed) {
	cameraPos += cameraSpeed * cameraUp;
}

//this function moves the camera down
void Camera::cameraDown(const float cameraSpeed) {
	cameraPos -= cameraSpeed * cameraUp;
}

//this function moves the camera forward
void Camera::cameraForward(const float cameraSpeed) {
	cameraPos += cameraSpeed * cameraFront;
}

//this function moves the camera back
void Camera::cameraBack(const float cameraSpeed) {
	cameraPos -= cameraSpeed * cameraFront;
}

//this function moves the camera to the left
void Camera::cameraLeft(const float cameraSpeed) {
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

//this function moves the camera to the right
void Camera::cameraRight(const float cameraSpeed) {
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

//this functions creates a matrix given the camera position to
//	transform the vertices in the world space to be relative to the camera
glm::mat4 Camera::view() {
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}


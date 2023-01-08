#include "../headers/Camera.h"

//constructor for camera class
Camera::Camera() {
	//define initial camera positions
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraU = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraR = glm::vec3(1.0f, 0.0f, 0.0f);
}

//this function moves the camera up
void Camera::cameraUp(const float cameraSpeed) {
	pitch += 6.0f * cameraSpeed;

	cameraU = glm::vec3(0.0f, cosf(glm::radians(pitch)), sinf(glm::radians(pitch)));
	cameraDirection = glm::cross(cameraR, cameraU);
	cameraPos = -glm::length(cameraPos) * glm::normalize(cameraDirection);
}

//this function moves the camera down
void Camera::cameraDown(const float cameraSpeed) {
	pitch -= 6.0f * cameraSpeed;

	cameraU = glm::vec3(0.0f, cosf(glm::radians(pitch)), sinf(glm::radians(pitch)));
	cameraDirection = glm::cross(cameraR, cameraU);
	cameraPos = -glm::length(cameraPos) * glm::normalize(cameraDirection);
}

//this function moves the camera forward
void Camera::cameraForward(const float cameraSpeed) {
	cameraPos += cameraSpeed * cameraDirection;
}

//this function moves the camera back
void Camera::cameraBack(const float cameraSpeed) {
	cameraPos -= cameraSpeed * cameraDirection;
}

//this function moves the camera to the left
void Camera::cameraLeft(const float cameraSpeed) {
	yaw -= 7.0f * cameraSpeed;

	cameraR = glm::vec3(cosf(glm::radians(yaw)), 0.0f, -sinf(glm::radians(yaw)));
	cameraDirection = glm::cross(cameraR, cameraU);
	cameraPos = -glm::length(cameraPos) * glm::normalize(cameraDirection);

}

//this function moves the camera to the right
void Camera::cameraRight(const float cameraSpeed) {
	yaw += 7.0f * cameraSpeed;

	cameraR = glm::vec3(cosf(glm::radians(yaw)), 0.0f, -sinf(glm::radians(yaw)));
	cameraDirection = glm::cross(cameraR, cameraU);
	cameraPos = -glm::length(cameraPos) * glm::normalize(cameraDirection);
}

//this functions creates a matrix given the camera position to
//	transform the vertices in the world space to be relative to the camera
glm::mat4 Camera::view() {
	return glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraU);
}


#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//this is the camera class
//defines functionality for camera movement around the scene
class Camera {
	//fields for class
	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	glm::vec3 cameraU;
	glm::vec3 cameraR;

	float pitch = 0.0f;
	float yaw = 0.0f;

public:

	//constructor for class
	Camera();

	//functions for class
	void cameraUp(const float cameraSpeed);
	void cameraDown(const float cameraSpeed);
	void cameraForward(const float cameraSpeed);
	void cameraBack(const float cameraSpeed);
	void cameraLeft(const float cameraSpeed);
	void cameraRight(const float cameraSpeed);
	glm::mat4 view();
};



#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//this is the camera class
//defines functionality for camera movement around the scene
class Camera {
private:
	//fields for class
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

public:

	//constructor for class
	Camera();

	//functions for class
	void cameraRaise(const float cameraSpeed);
	void cameraDown(const float cameraSpeed);
	void cameraForward(const float cameraSpeed);
	void cameraBack(const float cameraSpeed);
	void cameraLeft(const float cameraSpeed);
	void cameraRight(const float cameraSpeed);
	glm::mat4 view();
};



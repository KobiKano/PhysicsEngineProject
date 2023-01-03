#include "../headers/PhysicsBall.h"

//initialize logger
static Logger logger(Logger::info);

/*
This function calculates the position of the mouse in terms of vertex float (-1 to 1)
	given position in pixels
*/
void offset(GLfloat& xPos, GLfloat& yPos, GLFWwindow*window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	logger.debugLog("Window Dimensions: Width->" + std::to_string(width) + " Height->" + std::to_string(height) + "\n");
	xPos = (xPos - (width / 2)) / (width / 2);
	yPos = (yPos - (height / 2)) / (height / 2);
	logger.debugLog("Relative Position: xPos->" + std::to_string(xPos) + " yPos->" + std::to_string(yPos) + "\n");
}

//default constuctor
PhysicsBall::PhysicsBall() {}

//TODO actual implementation
PhysicsBall::PhysicsBall(GLfloat xPos, GLfloat yPos, GLFWwindow* window) {
	vertices = generate(xPos, yPos, window);
}

std::vector<GLfloat> PhysicsBall::generate(GLfloat xPos, GLfloat yPos, GLFWwindow* window) {
	//TODO actual implementation
	offset(xPos,yPos, window);
	std::vector<float> verts=
	{
		-0.5f + xPos, -0.5f * float(sqrt(3)) / 3 - yPos, 0.0f, // Lower left corner
		0.5f + xPos, -0.5f * float(sqrt(3)) / 3 - yPos, 0.0f, // Lower right corner
		0.0f + xPos, 0.5f * float(sqrt(3)) * 2 / 3 - yPos, 0.0f // Upper corner
	};
	return verts;
}

void PhysicsBall::move() {
	//TODO actual implementation
	vertices = vertices;
}
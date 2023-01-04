#pragma once

#include "headers/Logger.h"
#include <glad/glad.h>
#include <vector>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <string>

/*
Header file for PhysicsBall object
This is the object that will be used in all simulatons
Class defines all possible operations on vertices of object
*/
class PhysicsBall {
public:
	//field to store vertex information
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	//defualt constructor
	PhysicsBall();

	PhysicsBall(GLfloat radius, GLfloat xPos,GLfloat yPos, GLFWwindow* window);

	//functions for class
	void generate(GLfloat radius, GLfloat xPos, GLfloat yPos, GLFWwindow* window);

	void draw();
	void move();
};

#pragma once

#include "headers/Logger.h"
#include <glad/glad.h>
#include <string>

/*
This is the vertex buffer object class
This is part of the object rendering pipeline
*/
class VBO {
public:
	//ID to reference object
	GLuint ID;

	//default constructor
	VBO();

	//constructor that takes vertex data
	VBO(GLfloat* vertices, int size);

	//functions related to rendering object
	void assign();
	void unassign();
	void terminate();
};



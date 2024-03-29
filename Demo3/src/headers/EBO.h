#pragma once

#include "headers/Logger.h"
#include <glad/glad.h>
#include <string>

/*
This is the element buffer object class
This is part of the object rendering pipeline
*/
class EBO {
public:
	//ID to reference object
	GLuint ID;

	//default constructor
	EBO();

	//constructor that takes indices data
	EBO(GLuint* indices, int size);

	//functions related to rendering object
	void assign();
	void unassign();
	void terminate();
};

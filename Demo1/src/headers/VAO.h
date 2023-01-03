#pragma once

#include "headers/Logger.h"
#include<glad/glad.h>
#include "VBO.h"

/*
This class is a vertex array object
This class stores data related to the vertices so that they can be bound and unbound to the
	vertex buffer object easily
*/
class VAO {
public:
	//memory allocation ID for the VAO
	GLuint ID;

	//default constructor
	VAO();

	//generic constructor for the VAO
	VAO(int generic);

	//functionality related to VAO
	void linkVBO(VBO VBO, GLuint layout);
	void bind();
	void unbind();
	void terminate();
};

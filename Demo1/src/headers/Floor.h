#pragma once

#include <glad/glad.h>
#include <vector>
#include "headers/Logger.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

//this class creates a floor object for collisions to occur on
class Floor {
private:
	//private fields
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	VBO vertexBuffer;
	EBO elementBuffer;
	VAO vertexArray;

public:
	//constructor for class
	Floor();

	//functions related to class
	void draw();
};

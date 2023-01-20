#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include "headers/Logger.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

//creates a box object to render
class Box {
	//fields for class
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	VBO vertexBuffer;
	EBO elementBuffer;
	VAO vertexArray;

	//private functions for class
	void addNormalVertices();
public:
	//default constructor
	Box(float width, float height, float depth);

	//functions for class
	void draw();
};

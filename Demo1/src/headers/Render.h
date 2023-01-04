#pragma once

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "GLShaders.h"
#include "Shader.h"
#include "headers/Logger.h"
#include "PhysicsBall.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

//fields for rendering process
static PhysicsBall object;
static VBO vertexBuffer;
static EBO elementBuffer;
static VAO vertexArray;

//This class starts the rendering process for the demo
class Render {
	//fields used to initialize graphics
	Shader shaderProgram;
public:
	//default constructor
	Render();

	//constructor for render object
	Render(GLFWwindow* window);

	//functions for render object
	void terminate();
};


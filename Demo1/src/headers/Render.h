#pragma once

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLShaders.h"
#include "Shader.h"
#include "headers/Logger.h"
#include "PhysicsBall.h"
#include "VAO.h"
#include "Camera.h"
#include "Box.h"

//fields for rendering process
static std::vector<PhysicsBall*> objects;
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


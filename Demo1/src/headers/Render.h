#pragma once

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <thread>
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
#include "headers/Engine.h"

//fields for rendering process and physics
static std::vector<PhysicsBall*> objects;
static VAO vertexArray;
static int objectsAdded = 0;
static int objectsRemoved = 0;

//This class starts the rendering process for the demo
class Render {
	//fields used to initialize graphics and physics
	Shader shaderProgram;
	PhysicsEngine physicsEngine = PhysicsEngine(0.0001f);
public:
	//default constructor
	Render();

	//constructor for render object
	Render(GLFWwindow* window);

	//functions for render object
	void terminate();
};


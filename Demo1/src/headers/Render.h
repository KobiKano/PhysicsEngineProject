#ifndef RenderH
#define RenderH

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLShaders.h"
#include "Shader.h"
#include "PhysicsBall.h"
#include "VBO.h"
#include "VAO.h"

//This class starts the rendering process for the demo
class Render {
	//fields used to initialize graphics
	Shader shaderProgram;
	PhysicsBall object;
	VBO vertexBuffer;
	VAO vertexArray;
public:
	//default constructor
	Render();

	//constructor for render object
	Render(GLFWwindow* window);

	//functions for render object
	void terminate();
};

#endif


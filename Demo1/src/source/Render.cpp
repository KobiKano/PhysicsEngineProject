#include "../headers/Render.h"

using namespace std;

//intitialize logger
static Logger logger(Logger::info);

/*
* this function handles the creation of a sphere object
*/
void createSphereObject(GLdouble xPos, GLdouble yPos, GLFWwindow* window) {
	//create object
	object = PhysicsBall(0.1f/*radius*/, (GLfloat)xPos, (GLfloat)yPos, window);
	//logger to check if correct indices and vertices print
	logger.debugLog("vertices: ");
	for (int i = 0; i < object.vertices.size(); i++) {
		logger.debugLog(std::to_string(object.vertices[i]) + " ");
	}
	logger.debugLog("\n");
	logger.debugLog("indices: ");
	for (int i = 0; i < object.indices.size(); i++) {
		logger.debugLog(std::to_string(object.indices[i]) + " ");
	}
	logger.debugLog("\n");

	//write object to openGL
	vertexArray = VAO(0);
	vertexArray.bind();
	vertexBuffer = VBO(&object.vertices[0]);
	elementBuffer = EBO(&object.indices[0]);
	vertexArray.link(vertexBuffer, elementBuffer, 0);
}

/*
This fucntion checks the latest key press per frame
*/
void processInput(GLFWwindow* window) {
	//if the last key press was the escape key then the window will close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	//check if left click performed
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		//create object at mouse click location
		GLdouble xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		logger.debugLog("Mouse coords: xPos->" + std::to_string(xPos) + " yPos->" + std::to_string(yPos) + "\n");
		createSphereObject(xPos, yPos, window);
		//disallow processing of events for small amount of time to prevent spam
		glfwWaitEventsTimeout(0.4);
	}
}

//defualt constructor
Render::Render() {};

//this constructor begins the rendering process for the graphics objects
Render::Render(GLFWwindow* window) {
	logger.debugLog("starting rendering process\n");

	//initialize shaders
	shaderProgram = Shader(vert1, frag1);

	//add start buffer to window
	glfwSwapBuffers(window);

	logger.debugLog("finished initial render\n");

	//while loop to check if window close input detected
	//if detected returns true and program terminates
	//this is the generic render loop for the program
	while (!glfwWindowShouldClose(window)) {
		//set colors
		glClearColor(0.0144f, 0.360f, 0.354f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//define the shader
		shaderProgram.create();

		//checks latest key press
		processInput(window);

		//draw object
		object.draw();

		//checks for user interactions and updates current window buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	logger.debugLog("exiting render process\n");
}

//this function ends all rendering processes
void Render::terminate() {
	logger.debugLog("terminating render process\n");
	shaderProgram.terminate();
	vertexBuffer.terminate();
	elementBuffer.terminate();
	vertexArray.terminate();
}
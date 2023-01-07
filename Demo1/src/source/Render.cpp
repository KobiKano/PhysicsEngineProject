#include "../headers/Render.h"

using namespace std;

//intitialize logger
static Logger logger(Logger::info);

/*
* this function handles the creation of a sphere object
*/
void createSphereObject(GLdouble xPos, GLdouble yPos, GLFWwindow* window) {
	//create object
	GLfloat radius = 0.1f;
	PhysicsBall* object = new PhysicsBall(radius, (GLfloat)xPos, (GLfloat)yPos, window);
	
	//logger to check if correct indices and vertices print
	logger.debugLog("size of vertices: " + to_string(object->vertices.size()) + "\n");
	logger.debugLog("size of indices: " + to_string(object->indices.size()) + "\n");

	//but object in vector
	objects.push_back(object);
	logger.debugLog("Num PhysicsBalls: " + std::to_string(objects.size()) + "\n\n");
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

	//initialize object storage
	objects.clear();
	objects.reserve(20);  //max number of objects on screen
	logger.debugLog("num objects: " + std::to_string(objects.size()) + "\n");

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

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//draw objects
		for (int i = 0; i < objects.size(); i++) {
			//check if max size reached
			if (objects.size() == 20) {
				//delete first object
				delete objects.front();
				objects.erase(objects.begin());
			}
			//check if off screen
			if (!objects[i]->onScreen) {
				objects.erase(objects.begin() + i);
			}
			//draw objects
			objects[i]->draw();
		}

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
	vertexArray.terminate();
}
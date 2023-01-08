#include "../headers/Window.h"

using namespace std;

//initialize logger
static Logger logger(Logger::info);

/*
This fucntion defines functionality for window resizing
*/
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	//set viewport
	glViewport(0, 0, width, height);
	//assign colors to window
	glClearColor(0.2f, 0.0885f, 0.520f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT);
}

//default constructor
Window::Window() {};

Window::Window(int width, int height) {
	window = glfwCreateWindow(width, height, "PhysicsEngine", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		logger.errorLog("Error creating window.... Terminating program\n");
	}
	logger.debugLog("Window creation successful\n");
	//make window appear
	glfwMakeContextCurrent(window);

	//load glad for window coloring
	gladLoadGL();

	//create gl viewport
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

//this function terminates all window processes
void Window::terminate() {
	logger.debugLog("destroying window\n");
	glfwDestroyWindow(window);
}
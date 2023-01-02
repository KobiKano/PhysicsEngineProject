#include "../headers/Window.h"

using namespace std;

/*
This fucntion defines functionality for window resizing
*/
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	//set viewport
	glViewport(0, 0, width, height);
	//assign colors to window
	glClearColor(0.0144f, 0.360f, 0.354f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

//default constructor
Window::Window() {};

Window::Window(int width, int height) {
	window = glfwCreateWindow(width, height, "PhysicsEngine", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		cout << "Error creating window.... Terminating program";
	}
	cout << "Window creation successful\n";
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
	cout << "destroying window\n";
	glfwDestroyWindow(window);
}
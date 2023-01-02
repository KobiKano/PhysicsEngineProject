#ifndef WindowH
#define WindowH

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//this class starts the process of creating a window
class Window {
public:
	//window to be stored and accessed
	GLFWwindow* window;
	
	//default conststructor
	Window();

	//constructor for window object
	Window(int width, int height);

	//funtions for window
	void terminate();
};



#endif

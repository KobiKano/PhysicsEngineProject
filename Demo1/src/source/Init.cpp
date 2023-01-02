#include "../headers/Init.h"

//this is the constructor for the initialization class
//this class handles all the processes of the demo so that there is minimal clutter in the main class
Init::Init() {
	std::cout << "initialization started\n";
	createWindow();
	renderLoop();
	terminate();
}

//this function starts the window creation process
void Init::createWindow() {
	window = Window(800, 800);
}

//this function starts the render loop for the graphics
void Init::renderLoop() {
	render = Render(window.window);
}

//this function terminates all processes for the demo
void Init::terminate() {
	render.terminate();
	window.terminate();
}
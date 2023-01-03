#pragma once

#include "headers/Logger.h"
#include <iostream>
#include "Window.h"
#include "Render.h"

//This class handles all processes for the physics demo
class Init{
	//private fields
	Window window;
	Render render;
public:
	//default constructor
	Init();

	//functions for initialization
	void createWindow();
	void renderLoop();
	void terminate();
};

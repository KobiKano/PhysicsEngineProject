#include "../headers/Render.h"

using namespace std;

//intitialize logger
static Logger logger(Logger::info);

/*
* this function handles the creation of a sphere object
*/
void createSphereObject(GLFWwindow* window) {
	//create object
	GLfloat radius = 0.1f;
	PhysicsBall* object = new PhysicsBall(radius, window);
	
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
void processInput(GLFWwindow* window, Camera& camera, float deltaTime) {
	//if the last key press was the escape key then the window will close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//check if left click performed
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		//create object
		logger.debugLog("Left Mouse clicked!\n");
		createSphereObject(window);
		//disallow processing of events for small amount of time to prevent spam
		glfwWaitEventsTimeout(0.4);
	}

	//check if any camera movement occured
	const float cameraSpeed = 2.0f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.cameraForward(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.cameraBack(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.cameraLeft(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.cameraRight(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.cameraUp(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.cameraDown(cameraSpeed);

	//check if polygon state changed
	if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

	//create floor
	Box floor = Box();

	//initialize camera
	Camera camera = Camera();
	float currentFrame = 0.0f;
	float lastFrame = 0.0f;
	float deltaTime = 0.0f;
	int width, height;

	//add start buffer to window
	glfwSwapBuffers(window);

	logger.debugLog("finished initial render\n");

	//while loop to check if window close input detected
	//if detected returns true and program terminates
	//this is the generic render loop for the program
	while (!glfwWindowShouldClose(window)) {
		//set render parameters
		glClearColor(0.2f, 0.0885f, 0.520f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glCullFace(GL_FRONT);


		//define the shader
		shaderProgram.create();

		//assign transformation matrices
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		glfwGetWindowSize(window, &width, &height);
		view = camera.view();
		projection = glm::perspective(glm::radians(45.0f), (float)width / float(height), 0.1f, 100.0f);
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		int projLoc = glGetUniformLocation(shaderProgram.ID, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//set shader color for floor
		int objectcolor = glGetUniformLocation(shaderProgram.ID, "color");
		glUniform3f(objectcolor, 0.36f, 0.350f, 0.350f);

		//draw floor
		floor.draw();

		//check framerate
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		//checks latest key press
		processInput(window, camera, deltaTime);

		//set color for ball objects
		objectcolor = glGetUniformLocation(shaderProgram.ID, "color");
		glUniform3f(objectcolor, 0.76f, 0.722f, 0.722f);

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
		glDisable(GL_CULL_FACE);
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
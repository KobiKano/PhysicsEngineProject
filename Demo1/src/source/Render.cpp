#include "../headers/Render.h"

using namespace std;

/*
This fucntion checks the latest key press per frame
*/
void processInput(GLFWwindow* window) {
	//if the last key press was the escape key then the window will close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//defualt constructor
Render::Render() {};

//this constructor begins the rendering process for the graphics objects
Render::Render(GLFWwindow* window) {
	cout << "starting rendering process\n";

	//initialize shaders
	shaderProgram = Shader(vert1, frag1);

	//create object
	object = PhysicsBall(1);
	vertexArray = VAO(0);
	vertexArray.bind();
	vertexBuffer = VBO(&object.vertices[0], sizeof(object.vertices));
	vertexArray.linkVBO(vertexBuffer, 0);
	vertexArray.unbind();

	//add start buffer to window
	glfwSwapBuffers(window);

	cout << "finished initial render\n";

	//while loop to check if window close input detected
	//if detected returns true and program terminates
	//this is the generic render loop for the program
	while (!glfwWindowShouldClose(window)) {
		//checks latest key press
		processInput(window);

		//set colors
		glClearColor(0.0144f, 0.360f, 0.354f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//define the shader
		shaderProgram.create();
		//bind vertex data
		vertexArray.bind();
		//draw object
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//checks for user interactions and updates current window buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	cout << "exiting render process\n";
}

//this function ends all rendering processes
void Render::terminate() {
	cout << "terminating render process\n";
	shaderProgram.terminate();
	vertexBuffer.terminate();
	vertexArray.terminate();
}
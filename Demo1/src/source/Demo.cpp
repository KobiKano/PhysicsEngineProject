#include "../headers/Demo.h"

using namespace std;

int main() {
	cout << "Demo started\n";
	//initialize graphics
	glfwInit();

	//set version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//start demo
	Init();

	//end process with default return
	glfwTerminate();
	cout << "Demo exited\n";
	return 0;
}
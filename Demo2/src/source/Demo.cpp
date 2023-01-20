#include "../headers/Demo.h"

using namespace std;

int main() {
	//initialize logger
	static Logger logger(Logger::info);
	logger.infoLog("Demo started\n");
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
	logger.infoLog("Demo exited\n");
	return 0;
}
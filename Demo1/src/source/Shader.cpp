#include "../headers/Shader.h"

//default constructor
Shader::Shader() {}

//constructor for shader class
Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource) {
	//set ID in memory for shaders
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	//create shaders
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//assign shader source
	glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);

	//compile shaders
	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	//check if shader compilation successful
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}

	//set ID in memory for shader program
	ID = glCreateProgram();

	//attach shaders to shader program and link the program to the ID
	glAttachShader(ID, vertexShaderID);
	glAttachShader(ID, fragmentShaderID);
	glLinkProgram(ID);

	//check if link is successful
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(vertexShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" <<
			infoLog << std::endl;
	}

	//delete shaders since they are now stored in the shader program
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

//this function creates the shader program objects
void Shader::create() {
	glUseProgram(ID);
}

//this function unallocates memory used for the shaders
void Shader::terminate() {
	glDeleteProgram(ID);
}
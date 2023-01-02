#ifndef ShaderH
#define ShaderH

#include <glad/glad.h>
#include <iostream>

//this class creates shader objects to use in the graphics pipeline
class Shader {
	public:
		//ID to assign shaders to
		GLuint ID;
		//default constructor
		Shader();
		//constructor for the shader objects
		Shader(const char* vertShader, const char* fragShader);

		//functions for the shader class
		void create();
		void terminate();
};





#endif

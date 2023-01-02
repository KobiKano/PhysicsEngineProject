#include "../headers/VAO.h"

//default constructor
VAO::VAO() {};

//Constructor for VAO, assigns value to ID
VAO::VAO(int generic) {
	glGenVertexArrays(1, &ID);
}

//this function links a VBO to a VAO
void VAO::linkVBO(VBO VBO, GLuint layout) {
	//start VBO
	VBO.assign();

	//assign attributes to vertices
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(layout);

	//end VBO
	VBO.unassign();
}

//This function binds the VAO to the ID
void VAO::bind() {
	glBindVertexArray(ID);
}

//This function unbinds the VAO to the ID
void VAO::unbind() {
	glBindVertexArray(0);
}

//This function deletes the VAO from memory
void VAO::terminate() {
	glDeleteVertexArrays(1, &ID);
}
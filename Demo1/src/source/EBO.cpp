#include "../headers/EBO.h"

//default constructor
EBO::EBO() {};

//generates and assigns buffer for vertex data
EBO::EBO(GLuint* indices) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 9 * sizeof(indices), indices, GL_STATIC_DRAW);
}

//links buffer to ID
void EBO::assign() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

//un-links buffer from ID
void EBO::unassign() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//deletes the buffer
void EBO::terminate() {
	glDeleteBuffers(1, &ID);
}
#include "../headers/VBO.h"

//default constructor
VBO::VBO() {};

//generates and assigns buffer for vertex data
VBO::VBO(GLfloat* vertices) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(vertices), vertices, GL_STATIC_DRAW);
}

//links buffer to ID
void VBO::assign() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

//un-links buffer from ID
void VBO::unassign() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//deletes the buffer
void VBO::terminate() {
	glDeleteBuffers(1, &ID);
}
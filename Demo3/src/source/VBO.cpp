#include "../headers/VBO.h"

//initialize logger
static Logger logger(Logger::debug);

//default constructor
VBO::VBO() {};

//generates and assigns buffer for vertex data
VBO::VBO(GLfloat* vertices, int size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
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
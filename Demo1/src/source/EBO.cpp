#include "../headers/EBO.h"

//initialize logger
static Logger logger(Logger::debug);

//default constructor
EBO::EBO() {};

//generates and assigns buffer for vertex data
EBO::EBO(GLuint* indices, int size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	logger.debugLog("size of indices: " + std::to_string(size) + "\n");
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), indices, GL_STATIC_DRAW);
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
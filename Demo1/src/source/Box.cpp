#include "../headers/Box.h"

//initialize logger
Logger logger = Logger(Logger::debug);

//constructor for clas
Box::Box() {
	vertices.resize(8 * 3);
	indices.resize(12 * 3);

	//upper top left vertex (vertex 0)
	vertices[0] = -1.0f;
	vertices[1] = -0.9f;
	vertices[2] = -1.0f;

	//upper bottom left vertex (vertex 1)
	vertices[3] = -1.0f;
	vertices[4] = -0.9f;
	vertices[5] = 1.0f;

	//upper top right vertex (vertex 2)
	vertices[6] = 1.0f;
	vertices[7] = -0.9f;
	vertices[8] = -1.0f;

	//upper bottom right vertex (vertex 3)
	vertices[9] = 1.0f;
	vertices[10] = -0.9f;
	vertices[11] = 1.0f;

	//lower top left vertex (vertex 4)
	vertices[12] = -1.0f;
	vertices[13] = -1.0f;
	vertices[14] = -1.0f;

	//lower bottom left vertex (vertex 5)
	vertices[15] = -1.0f;
	vertices[16] = -1.0f;
	vertices[17] = 1.0f;

	//lower top right vertex (vertex 6)
	vertices[18] = 1.0f;
	vertices[19] = -1.0f;
	vertices[20] = -1.0f;

	//lower bottom right vertex (vertex 7)
	vertices[21] = 1.0f;
	vertices[22] = -1.0f;
	vertices[23] = 1.0f;

	//face 1
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 3;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	//face 2
	indices[6] = 0;
	indices[7] = 1;
	indices[8] = 5;
	indices[9] = 0;
	indices[10] = 4;
	indices[11] = 5;

	//face 3
	indices[12] = 0;
	indices[13] = 2;
	indices[14] = 6;
	indices[15] = 0;
	indices[16] = 4;
	indices[17] = 6;

	//face 4
	indices[18] = 2;
	indices[19] = 3;
	indices[20] = 7;
	indices[21] = 2;
	indices[22] = 6;
	indices[23] = 7;

	//face 5
	indices[24] = 3;
	indices[25] = 1;
	indices[26] = 5;
	indices[27] = 3;
	indices[28] = 7;
	indices[29] = 5;

	//face 6
	indices[30] = 4;
	indices[31] = 5;
	indices[32] = 7;
	indices[33] = 4;
	indices[34] = 6;
	indices[35] = 7;

	//bind to buffers
	vertexArray = VAO(1);
	vertexArray.bind();
	vertexBuffer = VBO(&vertices[0], vertices.size());
	elementBuffer = EBO(&indices[0], indices.size());
	vertexArray.link(vertexBuffer, elementBuffer, 0);
	logger.debugLog("Floor Created\n");
}

//this function writes objects to be rendered to openGL
void Box::draw() {
	vertexArray.bind();
	glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, 0);
}
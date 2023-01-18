#include "../headers/Floor.h"

//initialize logger
static Logger logger(Logger::debug);

//constructor creates a square floor for collisions
Floor::Floor() {
	vertices.resize(8 * 3);
	indices.resize(12 * 3);
	//upper top left corner (vertex 0)
	vertices[0] = -0.5f;
	vertices[1] = 0.1f;
	vertices[2] = -0.5f;

	//upper bottom left corner (vertex 1)
	vertices[3] = -0.5f;
	vertices[4] = 0.1f;
	vertices[5] = 0.5f;

	//upper top right corner (vertex 2)
	vertices[6] = 0.5f;
	vertices[7] = 0.1f;
	vertices[8] = -0.5;

	//upper bottom right corner (vertex 3)
	vertices[9] = 0.5f;
	vertices[10] = 0.1f;
	vertices[11] = 0.5f;

	//lower top left corner (vertex 4)
	vertices[12] = -0.5f;
	vertices[13] = 0.0f;
	vertices[14] = -0.5f;

	//lower bottom left corner (vertex 5)
	vertices[15] = -0.5f;
	vertices[16] = 0.0f;
	vertices[17] = 0.5f;

	//lower top right corner (vertex 6)
	vertices[18] = 0.5f;
	vertices[19] = 0.0f;
	vertices[20] = -0.5;

	//lower bottom right corner (vertex 7)
	vertices[21] = 0.5f;
	vertices[22] = 0.0f;
	vertices[23] = 0.5f;

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
	indices[9] = 4;
	indices[10] = 5;
	indices[11] = 0;

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

	//bind data to openGL
	vertexArray = VAO(1);
	vertexArray.bind();
	vertexBuffer = VBO(&vertices[0], vertices.size(), true);
	elementBuffer = EBO(&indices[0], indices.size(), true);
	vertexArray.link(vertexBuffer, elementBuffer, 0);
	logger.debugLog("Floor Created\n");
}

void Floor::draw() {
	vertexArray.bind();
	glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, 0);
}
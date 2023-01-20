#include "../headers/Box.h"

//initialize logger
Logger logger = Logger(Logger::debug);

//constructor for clas
Box::Box(float width, float height, float depth) {
	//allocate space for vectors
	vertices.resize(8 * 3);
	indices.resize(12 * 3);

	//upper top left vertex (vertex 0)
	vertices[0] = -width * 0.5f;
	vertices[1] = height * 0.5f;
	vertices[2] = -depth * 0.5f;

	//upper bottom left vertex (vertex 1)
	vertices[3] = -width * 0.5f;
	vertices[4] = height * 0.5f;
	vertices[5] = depth * 0.5f;

	//upper top right vertex (vertex 2)
	vertices[6] = width * 0.5f;
	vertices[7] = height * 0.5f;
	vertices[8] = -depth * 0.5f;

	//upper bottom right vertex (vertex 3)
	vertices[9] = width * 0.5f;
	vertices[10] = height * 0.5f;
	vertices[11] = depth * 0.5f;

	//lower top left vertex (vertex 4)
	vertices[12] = -width * 0.5f;
	vertices[13] = -height * 0.5f;
	vertices[14] = -depth * 0.5f;

	//lower bottom left vertex (vertex 5)
	vertices[15] = -width * 0.5f;
	vertices[16] = -height * 0.5f;
	vertices[17] = depth * 0.5f;

	//lower top right vertex (vertex 6)
	vertices[18] = width * 0.5f;
	vertices[19] = -height * 0.5f;
	vertices[20] = -depth * 0.5f;

	//lower bottom right vertex (vertex 7)
	vertices[21] = width * 0.5f;
	vertices[22] = -height * 0.5f;
	vertices[23] = depth * 0.5f;

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

	addNormalVertices();

	//bind to buffers
	vertexArray = VAO(1);
	vertexArray.bind();
	vertexBuffer = VBO(&vertices[0], vertices.size());
	elementBuffer = EBO(&indices[0], indices.size());
	vertexArray.link(vertexBuffer, elementBuffer, 0);
	logger.debugLog("Floor Created\n");
}

//This function helps add normal vector data to vertex data
void addNormalVectors(std::vector<GLfloat>& vertices, int index, GLfloat vertex[3], glm::vec3 normal) {
	vertices[index] = vertex[0];
	vertices[index + 1] = vertex[1];
	vertices[index + 2] = vertex[2];
	vertices[index + 3] = normal[0];
	vertices[index + 4] = normal[1];
	vertices[index + 5] = normal[2];
}

//this function adds normal vertices to object
void Box::addNormalVertices() {
	//copy vertices and indices data
	std::vector<GLfloat> verticesCopy = std::vector<GLfloat>(vertices);
	std::vector<GLuint> indicesCopy = std::vector<GLuint>(indices);
	vertices.clear();
	indices.clear();

	//allocate memory for vertices
	vertices.resize(verticesCopy.size() * 9);
	indices.resize(indicesCopy.size());
	int vIndex = 0;
	int iIndex = 0;

	GLfloat vertex1[3], vertex2[3], vertex3[3];
	glm::vec3 vector1, vector2, normalVector;

	//for loop to iterate through all triangles
	for (int i = 0; i < indicesCopy.size(); i += 3) {
		//assign vertices
		vertex1[0] = verticesCopy[indicesCopy[i] * 3];
		vertex1[1] = verticesCopy[indicesCopy[i] * 3 + 1];
		vertex1[2] = verticesCopy[indicesCopy[i] * 3 + 2];
		vertex2[0] = verticesCopy[indicesCopy[i + 1] * 3];
		vertex2[1] = verticesCopy[indicesCopy[i + 1] * 3 + 1];
		vertex2[2] = verticesCopy[indicesCopy[i + 1] * 3 + 2];
		vertex3[0] = verticesCopy[indicesCopy[i + 2] * 3];
		vertex3[1] = verticesCopy[indicesCopy[i + 2] * 3 + 1];
		vertex3[2] = verticesCopy[indicesCopy[i + 2] * 3 + 2];

		//find vectors of triangle
		vector1 = glm::vec3(vertex2[0] - vertex1[0], vertex2[1] - vertex1[1], vertex2[2] - vertex1[2]);
		vector2 = glm::vec3(vertex3[0] - vertex1[0], vertex3[1] - vertex1[1], vertex3[2] - vertex1[2]);

		//find normal vector
		normalVector = glm::cross(vector1, vector2);
		normalVector = glm::normalize(normalVector);

		logger.debugLog("Normal vector: " + std::to_string(normalVector[0]) + " " + std::to_string(normalVector[1]) + " " + std::to_string(normalVector[2]) + "\n");

		//add normal vector for each point
		addNormalVectors(vertices, vIndex, vertex1, normalVector);
		addNormalVectors(vertices, vIndex + 6, vertex2, normalVector);
		addNormalVectors(vertices, vIndex + 12, vertex3, normalVector);
		vIndex += 18;

		//add indices
		indices[iIndex] = iIndex;
		indices[iIndex + 1] = iIndex + 1;
		indices[iIndex + 2] = iIndex + 2;
		iIndex += 3;
	}
}

//this function writes objects to be rendered to openGL
void Box::draw() {
	vertexArray.bind();
	glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, 0);
}
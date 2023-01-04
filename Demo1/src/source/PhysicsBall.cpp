#include "../headers/PhysicsBall.h"

//initialize logger
static Logger logger(Logger::info);

/*
This function calculates the position of the mouse in terms of vertex float (-1 to 1)
	given position in pixels
*/
void offset(GLfloat& xPos, GLfloat& yPos, GLFWwindow* window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	logger.debugLog("Window Dimensions: Width->" + std::to_string(width) + " Height->" + std::to_string(height) + "\n");
	xPos = (xPos - (width / 2)) / (width / 2);
	yPos = (yPos - (height / 2)) / (height / 2);
	logger.debugLog("Relative Position: xPos->" + std::to_string(xPos) + " yPos->" + std::to_string(yPos) + "\n");
}

/*
This function generates an octahedron based on where the user clicked and a given radius
The vertices of the octahedron are then stored in the vertices and indices fields
*/
void generateOctahedron(GLfloat radius, GLfloat xPos, GLfloat yPos, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {
	//preallocate memory for vertices and indices
	vertices.resize(18);
	indices.resize(24);
	//create octahedron vertices from xPos and yPos
	//vertex 1 (rightmost)
	vertices[0] = (xPos + radius);
	vertices[1] = (yPos);
	vertices[2] = (0.0f);
	//vertex 2 (furthest)
	vertices[3] = (xPos);
	vertices[4] = (yPos);
	vertices[5] = (-radius);
	//vertex 3 (top)
	vertices[6] = (xPos);
	vertices[7] = (yPos + radius);
	vertices[8] = (0.0f);
	//vertex 4 (leftmost)
	vertices[9] = (xPos - radius);
	vertices[10] = (yPos);
	vertices[11] = (0.0f);
	//vertex 5 (closest)
	vertices[12] = (xPos);
	vertices[13] = (yPos);
	vertices[14] = (radius);
	//vertex 6 (bottom)
	vertices[15] = (xPos);
	vertices[16] = (yPos - radius);
	vertices[17] = (0.0f);

	//assign octahedron indices
	//surface 1
	indices[0] = (1);
	indices[1] = (2);
	indices[2] = (3);
	//surface 2
	indices[3] = (2);
	indices[4] = (4);
	indices[5] = (3);
	//surface 3
	indices[6] = (4);
	indices[7] = (5);
	indices[8] = (3);
	//surface 4
	indices[9] = (5);
	indices[10] = (1);
	indices[11] = (3);
	//surface 5
	indices[12] = (1);
	indices[13] = (2);
	indices[14] = (6);
	//surface 6
	indices[15] = (2);
	indices[16] = (4);
	indices[17] = (6);
	//surface 7
	indices[18] = (4);
	indices[19] = (5);
	indices[20] = (6);
	//surface 8
	indices[21] = (5);
	indices[22] = (1);
	indices[23] = (6);
}

/*
This function takes triangular surface (groups of three vertices) and subdivides them into more triangles
*/
void subdivideSurfaces(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices) {
	
}

/*
This function takes an octahedron with subdivided surfaces and normalized each vertex to be a distance of radius from the center point
*/
void normalizeVertices(GLfloat radius, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {

}

//default constuctor
PhysicsBall::PhysicsBall() {}

//TODO actual implementation
PhysicsBall::PhysicsBall(GLfloat radius, GLfloat xPos, GLfloat yPos, GLFWwindow* window) {
	generate(radius, xPos, yPos, window);
}

void PhysicsBall::generate(GLfloat radius, GLfloat xPos, GLfloat yPos, GLFWwindow* window) {
	offset(xPos, yPos, window);
	generateOctahedron(radius, xPos, yPos, vertices, indices);
}

void PhysicsBall::draw() {
	glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, 0);
}

void PhysicsBall::move() {
	//TODO actual implementation
	vertices = vertices;
}
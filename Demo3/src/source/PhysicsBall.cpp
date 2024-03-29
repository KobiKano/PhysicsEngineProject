#include "../headers/PhysicsBall.h"

//initialize logger
static Logger logger(Logger::info);

/*
This function generates an Icosahedron based on where the user clicked and a given radius
The vertices of the octahedron are then stored in the vertices and indices fields
*/
void generateIcosahedron(GLfloat radius, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {
	//clear and preallocate memory for vertices and indices
	vertices.clear();
	indices.clear();
	vertices.resize(12 * 3); //12 vertices on isohedron
	indices.resize(20 * 3); //20 faces on isohedron

	//generate vertices
	//use spherical coordinate system to find cartesian coordinates of vertex points
	//start with northern-most vertex at {0,rad,0} (vertex 0)
	vertices[0] = 0.0f;
	vertices[1] = radius;
	vertices[2] = 0.0f;

	//create all vertices with angle arctan(0.5rad) from xz plane (vertices 1 - 5)
	/*NOTE: Spherical to cartesian coordinate translation is different here because of relative axis
		y
		|                  Theta is defined as angle from xz plane to vertex
		|                  Phi is defined as angle from yz plane to vertex
		|
		|_________x
		/
	   /
	  /
	 z
	*/	
	const GLfloat pi = 3.1415926f;
	const GLfloat theta = atanf(0.5f);
	const GLfloat deltaPhi = (72 * pi)/180;  //convert degrees to radians
	GLfloat phi = 0;
	for (int i = 3; i < 16; i+=3) {
		//assign vertices based on spherical to cartesian translation
		vertices[i] = radius * cosf(theta) * sinf(phi);
		vertices[i + 1] = radius * sinf(theta);
		vertices[i + 2] = radius * cosf(theta) * cosf(phi);
		phi += deltaPhi;
	}

	//create all vertices with angle -arctan(0.5) from xz plane (vertices 6 - 10)
	phi = (36 * pi)/180;
	for (int i = 18; i < 31; i+=3) {
		vertices[i] = radius * cosf(-theta) * sinf(phi);
		vertices[i + 1] = radius * sinf(-theta);
		vertices[i + 2] = radius * cosf(-theta) * cosf(phi);
		phi += deltaPhi;
	}

	//create southern most vertex at {0, -rad, 0} (vertex 11)
	vertices[33] = 0.0f;
	vertices[34] = -radius;
	vertices[35] = 0.0f;

	//assign indices
	//face 1
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	//face 2
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	//face 3
	indices[6] = 0;
	indices[7] = 3;
	indices[8] = 4;

	//face 4
	indices[9] = 0;
	indices[10] = 4;
	indices[11] = 5;

	//face 5
	indices[12] = 0;
	indices[13] = 5;
	indices[14] = 1;

	//face 6
	indices[15] = 1;
	indices[16] = 2;
	indices[17] = 6;

	//face 7
	indices[18] = 6;
	indices[19] = 7;
	indices[20] = 2;

	//face 8
	indices[21] = 2;
	indices[22] = 3;
	indices[23] = 7;

	//face 9
	indices[24] = 7;
	indices[25] = 8;
	indices[26] = 3;

	//face 10
	indices[27] = 3;
	indices[28] = 4;
	indices[29] = 8;

	//face 11
	indices[30] = 8;
	indices[31] = 9;
	indices[32] = 4;

	//face 12
	indices[33] = 4;
	indices[34] = 5;
	indices[35] = 9;

	//face 13
	indices[36] = 9;
	indices[37] = 10;
	indices[38] = 5;

	//face 14
	indices[39] = 5;
	indices[40] = 1;
	indices[41] = 10;

	//face 15
	indices[42] = 10;
	indices[43] = 6;
	indices[44] = 1;

	//face 16
	indices[45] = 11;
	indices[46] = 6;
	indices[47] = 7;

	//face 17
	indices[48] = 11;
	indices[49] = 7;
	indices[50] = 8;

	//face 18
	indices[51] = 11;
	indices[52] = 8;
	indices[53] = 9;

	//face 19
	indices[54] = 11;
	indices[55] = 9;
	indices[56] = 10;

	//face 20
	indices[57] = 11;
	indices[58] = 10;
	indices[59] = 6;
}

//this function finds the midpoint of all edges of a triangle
void computeHalfVertex(GLfloat radius, const GLfloat v1[3], const GLfloat v2[3], GLfloat newV[3]) {
	newV[0] = (v1[0] + v2[0])/2;    // x
	newV[1] = (v1[1] + v2[1])/2;    // y
	newV[2] = (v1[2] + v2[2])/2;    // z
}

//this function adds a triangle of vertices to the vector
void addVertices(int index, GLfloat* v1, GLfloat* v2, GLfloat* v3, std::vector<GLfloat>& vertices) {
	//iterates through vertex arrays and adds each triangle to vertices
	for (int i = 0; i < 3; i++) {
		vertices[index] = v1[i];
		vertices[index + 3] = v2[i];
		vertices[index + 6] = v3[i];
		
		//increment index
		index++;
	}
}

//This function adds a triangle of indices to the vector
void addIndices(int index, GLuint i1, GLuint i2, GLuint i3, std::vector<GLuint>& indices) {
	indices[index] = i1;
	indices[index + 1] = i2;
	indices[index + 2] = i3;
}

/*
This function takes triangular surface (groups of three vertices) and subdivides them into more triangles
*/
void subdivideSurfaces(GLfloat radius, std::vector<GLfloat> &vertices, std::vector<GLuint> &indices) {
	//local variables to be used for computation
	std::vector<GLfloat> tmpVertices;
	std::vector<GLuint> tmpIndices;
	GLfloat* v1, * v2, * v3;          // ptr to original vertices of a triangle
	GLfloat newV1[3], newV2[3], newV3[3]; // new vertex positions
	unsigned int iIndex;
	unsigned int vIndex;
	int subdivisions = 3;  //using only 3 subdivisions as this is as far as necissary to get a spherical resemblance

	//iterate all subdivision levels
	for (int i = 1; i <= subdivisions; ++i)
	{
		//copy prev vertex/index arrays and clear
		tmpVertices = vertices;
		tmpIndices = indices;
		vertices.clear();
		indices.clear();

		//set new size of vertices and indices
		vertices.resize(tmpVertices.size() * 20);
		indices.resize(tmpIndices.size() * 4);
		iIndex = 0;
		vIndex = 0;

		//perform subdivision for each triangle
		for (int j = 0; j < tmpIndices.size(); j += 3)
		{
			//get 3 vertices of a triangle
			v1 = &tmpVertices[tmpIndices[j] * 3];
			v2 = &tmpVertices[tmpIndices[j + 1] * 3];
			v3 = &tmpVertices[tmpIndices[j + 2] * 3];

			// compute 3 new vertices by spliting half on each edge
			//         v1       
			//        / \       
			// newV1 *---* newV3
			//      / \ / \     
			//    v2---*---v3   
			//       newV2      
			computeHalfVertex(radius, v1, v2, newV1);
			computeHalfVertex(radius, v2, v3, newV2);
			computeHalfVertex(radius, v1, v3, newV3);

			//add 4 new triangles to vertex array
			addVertices(vIndex, v1, newV1, newV3, vertices);
			addVertices(vIndex + 9,newV1, v2, newV2, vertices);
			addVertices(vIndex + 18, newV1, newV2, newV3, vertices);
			addVertices(vIndex + 27,  newV3, newV2, v3, vertices);

			//add indices of 4 new triangles
			addIndices(iIndex, iIndex, iIndex + 1, iIndex + 2, indices);
			addIndices(iIndex + 3, iIndex + 3, iIndex + 4, iIndex + 5, indices);
			addIndices(iIndex + 6, iIndex + 6, iIndex + 7, iIndex + 8, indices);
			addIndices(iIndex + 9, iIndex + 9, iIndex + 10, iIndex + 11, indices);
			iIndex += 12;    // indices next index
			vIndex += 36;	 // vertices next index
		}
	}
}

/*
This function translates all vertices to be a specific distance of radius from the centerpoint of the Icosahedron
	resulting in a icosphere
*/
void normalizeVertices(GLfloat radius, std::vector<GLfloat> &vertices) {
	//define center point as (0,0,0)
	GLfloat center[3] = {0.0f, 0.0f, 0.0f};

	//temp variables used to store values for this operation
	GLfloat deltaX;
	GLfloat deltaY;
	GLfloat deltaZ;
	GLfloat distance;

	//iterate through all vertices
	for (int i = 0; i < vertices.size(); i+=3) {
		//find distance between vertices and center
		deltaX = vertices[i] - center[0];
		deltaY = vertices[i + 1] - center[1];
		deltaZ = vertices[i + 2] - center[2];

		//find magnitude of distance using distance formula
		distance = sqrtf(powf(deltaX, 2) + powf(deltaY, 2) + powf(deltaZ, 2));

		//find distance we want to modify vertex by
		deltaX = deltaX * radius / distance;
		deltaY = deltaY * radius / distance;
		deltaZ = deltaZ * radius / distance;

		//change vertices to match new normalized positions
		vertices[i] =  deltaX;
		vertices[i + 1] = deltaY;
		vertices[i + 2] = deltaZ;
	}
}

//This function helps add normal vector data to vertex data
void addNormalVector(std::vector<GLfloat>& vertices, int index, GLfloat vertex[3], glm::vec3 normal) {
	vertices[index] = vertex[0];
	vertices[index + 1] = vertex[1];
	vertices[index + 2] = vertex[2];
	vertices[index + 3] = normal[0];
	vertices[index + 4] = normal[1];
	vertices[index + 5] = normal[2];
}

//this function finds normal vectors for each vertex
void addNormalVertices(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {
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
	GLfloat centerOfTriangle[3];
	GLfloat midPoint[3];
	glm::vec3 normalVector;

	//for loop to iterate through all triangles
	for (int i = 0; i < indicesCopy.size(); i+=3) {
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

		//find center of triangle
		midPoint[0] = (vertex1[0] + vertex2[0]) * 0.5f;
		midPoint[1] = (vertex1[1] + vertex2[1]) * 0.5f;
		midPoint[2] = (vertex1[2] + vertex2[2]) * 0.5f;

		centerOfTriangle[0] = (midPoint[0] + vertex3[0]) * 0.5f;
		centerOfTriangle[1] = (midPoint[1] + vertex3[1]) * 0.5f;
		centerOfTriangle[2] = (midPoint[2] + vertex3[2]) * 0.5f;

		//find normal vector
		normalVector = glm::vec3(centerOfTriangle[0], centerOfTriangle[1], centerOfTriangle[2]);
		glm::normalize(normalVector);

		//add normal vector for each point
		addNormalVector(vertices, vIndex, vertex1, normalVector);
		addNormalVector(vertices, vIndex + 6, vertex2, normalVector);
		addNormalVector(vertices, vIndex + 12, vertex3, normalVector);
		vIndex += 18;

		//add indices
		indices[iIndex] = iIndex;
		indices[iIndex + 1] = iIndex + 1;
		indices[iIndex + 2] = iIndex + 2;
		iIndex += 3;
	}
}

//default constuctor
PhysicsBall::PhysicsBall() {}

//default destructor
PhysicsBall::~PhysicsBall() {
	logger.debugLog("PhysicsBall destroyed\n");
	vertexBuffer.terminate();
	elementBuffer.terminate();
	vertexArray.terminate();
}

//this is the constructor for the class
PhysicsBall::PhysicsBall(GLfloat radius, GLFWwindow* window, std::string name) {
	this->name = name;
	position[0] = 0.0f;
	position[1] = 1.0f;
	position[2] = 0.0f;
	generate(radius, window);
}

void PhysicsBall::generate(GLfloat radius, GLFWwindow* window) {
	//create the IcoSphere
	generateIcosahedron(radius, vertices, indices);
	subdivideSurfaces(radius, vertices, indices);
	normalizeVertices(radius, vertices);
	addNormalVertices(vertices, indices);
	//move created object to be centered around mouse click position
	//bind data to openGL
	vertexArray = VAO(1);
	vertexArray.bind();
	vertexBuffer = VBO(&vertices[0], vertices.size());
	elementBuffer = EBO(&indices[0], indices.size());
	vertexArray.link(vertexBuffer, elementBuffer, 0);
	onScreen = true;
	logger.debugLog("PhysicsBall Created\n");
}

//this function handles the actual rendering of the object to the screen
void PhysicsBall::draw() {
	//check if vertices off screen
	for (int i = 0; i < 3; i++) {
		if (position[i] > 10.0f || position[i] < -10.0f) {
			onScreen = false;
		}
	}

	//write object to openGL
	vertexArray.bind();
	glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, 0);
}
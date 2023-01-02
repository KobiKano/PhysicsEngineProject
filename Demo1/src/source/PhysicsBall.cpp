#include "../headers/PhysicsBall.h"


//default constuctor
PhysicsBall::PhysicsBall() {}

//TODO actual implementation
PhysicsBall::PhysicsBall(int size) {
	vertices = generate(size);
}

std::vector<GLfloat> PhysicsBall::generate(int size) {
	//TODO actual implementation
	std::vector<float> verts=
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};
	return verts;
}

void PhysicsBall::move() {
	//TODO actual implementation
	vertices = vertices;
}
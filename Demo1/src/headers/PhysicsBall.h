#ifndef PhysicsBallH
#define PhysicsBallH

#include <glad/glad.h>
#include<vector>

/*
Header file for PhysicsBall object
This is the object that will be used in all simulatons
Class defines all possible operations on vertices of object
*/
class PhysicsBall {
public:
	//field to store vertex information
	std::vector<GLfloat> vertices;

	//defualt constructor
	PhysicsBall();

	PhysicsBall(int);

	//functions for class
	std::vector<GLfloat> generate(int);
	void move();
};

#endif

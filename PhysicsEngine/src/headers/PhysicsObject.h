#pragma once

#include <vector>
#include <string>
#include "Logger.h"
#include "Force.h"

//this class stores data related to every registered object in the physics engine
class PhysicsObject {
public:
	//these enums define the properties of registered objects
	enum ObjectType {
		PHYSICS_RIGID_BODY = 0, PHYSICS_SOFT_BODY, PHYSICS_STATIC
	};
	enum ObjectShape {
		PHYSICS_SPHERE = 0, PHYSICS_CUBE
	};

private:
	//these fields are used to store information about the object
	float centerPos[3];
	float radius;
	std::string name;
	ObjectType objectType;
	ObjectShape objectShape;
	float velocity[3];
	float mass;

public:
	std::vector<Force> forces;
	//constructor for class
	PhysicsObject(float centerPos[3], float radius, std::string name, ObjectType objectType, ObjectShape objectShape, float mass);

	//functions for class
	float* getCenterPos();
	void setCenterPos(float centerPoint[3]);
	void addForce(Force::ForceType force, float magnitude, float direction[3]);
	float* getVelocity();
	void setVelocity(float newVelocity[3]);
	float getMass();
	void setMass(float mass);
	float getRadius();
	std::string getName();
	ObjectType getObjectType();
	ObjectShape getObjectShape();
};

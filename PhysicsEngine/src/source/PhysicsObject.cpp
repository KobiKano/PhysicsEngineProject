#include "../headers/PhysicsObject.h"

//initialize logger
static Logger logger = Logger(Logger::debug);

//This is the constructor for the physics object class
PhysicsObject::PhysicsObject(float centerPos[3], float radius, std::string name, ObjectType objectType, ObjectShape objectShape, float mass) {
	//initialize fields
	this->name = name;
	this->objectType = objectType;
	this->objectShape = objectShape;
	this->radius = radius;
	setCenterPos(centerPos);
	setMass(mass);
	velocity[0] = 0.0f;
	velocity[1] = 0.0f;
	velocity[2] = 0.0f;
}

//this function gets the center position of the object to find where the object is
float* PhysicsObject::getCenterPos() {
	return centerPos;
}

//this function sets the center position of the object when the object is moved
void PhysicsObject::setCenterPos(float centerPos[3]) {
	this->centerPos[0] = centerPos[0];
	this->centerPos[1] = centerPos[1];
	this->centerPos[2] = centerPos[2];
}

//this function adds a new force to an object
void PhysicsObject::addForce(Force::ForceType force, float magnitude, float* direction) {
	forces.push_back(Force::Force(force, magnitude, direction));
	logger.debugLog("force magnitude: " + std::to_string(forces[forces.size() - 1].magnitude) + "\n");
	logger.debugLog("force direction.x: " + std::to_string(forces[forces.size() - 1].direction[0]) + "\n");
	logger.debugLog("force direction.x: " + std::to_string(forces[forces.size() - 1].direction[1]) + "\n");
	logger.debugLog("force direction.x: " + std::to_string(forces[forces.size() - 1].direction[2]) + "\n");
}

//this function gets the current velocity of the object
float* PhysicsObject::getVelocity() {
	return velocity;
}

//this function sets a new velocity for the object
void PhysicsObject::setVelocity(float newVelocity[3]) {
	velocity[0] = newVelocity[0];
	velocity[1] = newVelocity[1];
	velocity[2] = newVelocity[2];
}

float PhysicsObject::getMass() {
	return mass;
}

void PhysicsObject::setMass(float mass) {
	this->mass = mass;
}

//this function gets the radius of the object to help calculate collisions
float PhysicsObject::getRadius() {
	return radius;
}

//this function gets the name of the object for storage in a hashmap
std::string PhysicsObject::getName() {
	return name;
}

//this function gets the object type
PhysicsObject::ObjectType PhysicsObject::getObjectType() {
	return objectType;
}

//this function gets the object shape
PhysicsObject::ObjectShape PhysicsObject::getObjectShape() {
	return objectShape;
}

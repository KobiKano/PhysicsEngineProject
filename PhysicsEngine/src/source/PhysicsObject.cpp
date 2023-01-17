#include "../headers/PhysicsObject.h"

//initialize logger
static Logger logger = Logger(Logger::info);

//This is the constructor for the physics object class
PhysicsObject::PhysicsObject(float centerPos[3], float radius[3], std::string name, ObjectType objectType, ObjectShape objectShape, float mass) {
	//initialize fields
	this->name = name;
	this->objectType = objectType;
	this->objectShape = objectShape;
	setCenterPos(centerPos);
	setMass(mass);

	this->radius[0] = radius[0]; //x
	this->radius[1] = radius[1]; //y
	this->radius[2] = radius[2]; //z
	
	velocity[0] = 0.0f; //x
	velocity[1] = 0.0f; //y
	velocity[2] = 0.0f; //z
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
	logger.debugLog("centerPos.x = " + std::to_string(centerPos[0]) + "\n");
	logger.debugLog("centerPos.y = " + std::to_string(centerPos[1]) + "\n");
	logger.debugLog("centerPos.z = " + std::to_string(centerPos[2]) + "\n");
}

//this function adds a new force to an object
void PhysicsObject::addForce(Force::ForceType force, float magnitude, float direction[3]) {
	forces.push_back(Force::Force(force, magnitude, direction));
	logger.debugLog("force magnitude: " + std::to_string(forces[forces.size() - 1].magnitude) + "\n");
	logger.debugLog("force direction.x: " + std::to_string(forces[forces.size() - 1].direction[0]) + "\n");
	logger.debugLog("force direction.y: " + std::to_string(forces[forces.size() - 1].direction[1]) + "\n");
	logger.debugLog("force direction.z: " + std::to_string(forces[forces.size() - 1].direction[2]) + "\n");
}

//this function removes a force from an object
void PhysicsObject::removeForce(Force::ForceType force, float magnitude, float direction[3]) {
	for (int i = 0; i < forces.size(); i++) {
		if (force == forces[i].forceType && magnitude == forces[i].magnitude && direction[0] == forces[i].direction[0]
			&& direction[1] == forces[i].direction[1] && direction[2] == forces[i].direction[2]) {
			forces.erase(std::vector<Force>::iterator(forces.begin() + i));
		}
	}
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
float* PhysicsObject::getRadius() {
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

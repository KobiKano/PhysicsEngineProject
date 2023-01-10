#include "../headers/Engine.h"

//initialize logger
static Logger logger = Logger(Logger::debug);

//This function maps a new object to the map of physics objects
void PhysicsEngine::registerObject(float* centerPos, float radius, std::string name, PhysicsObject::ObjectType objectType, PhysicsObject::ObjectShape objectShape, float mass) {
	objectTable[name] = new PhysicsObject(centerPos, radius, name, objectType, objectShape, mass);
	logger.debugLog("objectTable size: " + std::to_string(objectTable.size()) + "\n");
}

//this function removes an object from the map of physics objects
void PhysicsEngine::deleteObject(std::string name) {
	objectTable.erase(name);
}

//this function adds a force on an object
void PhysicsEngine::addForce(std::string name, Force::ForceType force, float constant, float* direction) {
	objectTable[name]->addForce(force, constant, direction);
}

//this function fetches the current position of the object
float* PhysicsEngine::getPosition(std::string name) {
	return objectTable[name]->getCenterPos();
}

//this function updates the position of the object
void PhysicsEngine::updatePosition(std::string name, float deltaTime) {
	PhysicsObject* currObject = objectTable[name];
	PhysicsHandler handler = PhysicsHandler(currObject, deltaTime);
}

//this function deletes all heap allocated memory of a physics object
void PhysicsEngine::terminate() {
	std::map<std::string, PhysicsObject*>::iterator iterator = objectTable.begin();

	while (iterator != objectTable.end()) {
		delete iterator->second;
		iterator++;
	}

	objectTable.clear();
}
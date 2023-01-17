#pragma once

#include <string>
#include <map>
#include "Logger.h"
#include "PhysicsObject.h"
#include "PhysicsHandler.h"
#include "Force.h"
#include "CollisionHandler.h"

//this is the main class for the physics engine
//all functions related to the physics engine are defined here
class PhysicsEngine {
	//this is the map that stores all registered objects
	std::map <std::string, PhysicsObject*> objectTable;
	float airResistance;
	CollisionHandler collisionHandler;
public:

	//default constructor
	PhysicsEngine();

	//this is the constructor for this class
	PhysicsEngine(float airResistance);

	//This function maps a new object to the map of physics objects
	void registerObject(float* centerPos, float radius[3], std::string name, PhysicsObject::ObjectType objectType, PhysicsObject::ObjectShape objectShape, float mass);

	//this function removes an object from the map of physics objects
	void deleteObject(std::string name);

	//this function adds a force on an object
	void addForce(std::string name, Force::ForceType force, float constant, float* direction);

	//this function removes a force on an object
	void removeForce(std::string name, Force::ForceType force, float constant, float* direction);

	//this function fetches the current position of the object
	float* getPosition(std::string name);

	//this function checks for collisions
	void checkCollisions(std::string name);

	//this function updates the position of the object
	void updatePosition(std::string name, float deltaTime);

	//this function deletes all heap allocated memory of a physics object
	void terminate();

};



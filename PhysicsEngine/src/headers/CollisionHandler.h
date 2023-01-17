#pragma once

#include<map>
#include <string>
#include "PhysicsObject.h"

//this class is used to handle all collisions within the physics world
class CollisionHandler {
	//struct used to store info about each cubic space for collisions
	struct Container {
		//bounds for cube
		float lowerBoundX;
		float upperBoundX;

		//vector to store objects within these bounds
		std::vector<PhysicsObject*> objects;
	};

	//private fields for this class
	std::map<std::string, PhysicsObject*>* objectMap;
	float percentEnergyRemaining;
	std::vector<Container> possibleCollisions;
	std::map<PhysicsObject*, PhysicsObject*> collisionMap;

	//private functions to find collisions
	void findPossibleCollisions();
	void checkCollisions();
	void resolveCollsions();
public:
	//default constructor
	CollisionHandler();

	//constructor for class
	CollisionHandler(std::map<std::string, PhysicsObject*>* objectMap ,float percentEnergyRemaining);

	//functions for class
	void calcCollisions();
};

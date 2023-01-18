#include "../headers/CollisionHandler.h"

//default constructor
CollisionHandler::CollisionHandler() {
	objectMap = nullptr;
}

//constructor for class
CollisionHandler::CollisionHandler(std::map<std::string, PhysicsObject*>* objectMap, float percentEnergyRemaining) {
	this->objectMap = objectMap;
	this->percentEnergyRemaining = percentEnergyRemaining;
}

/*
This function uses grid mapping to find areas where possible collisions could occur
considers x, y, and z axis to have values of -5 to 5
divides #D space into cubes by taking steps of 0.5 through each axis
if two objects are within the same cube, add to objects vector
*/
void CollisionHandler::findPossibleCollisions() {
	std::map<std::string, PhysicsObject*>::iterator iterator;

	//check if objects within x bounds
	for (float i = -5.0f; i < 5.0f; i += 0.5f) {
		iterator = objectMap->begin();
		//while loop to iterate though objectMap
		while (iterator != objectMap->end()) {
			//initialize container
			Container container;
			container.lowerBoundX = i;
			container.upperBoundX = i + 0.5f;
			std::vector<PhysicsObject*> objects;

			//check if any part of object falls within bounds
			if (iterator->second->getCenterPos()[0] > i && iterator->second->getCenterPos()[0] < i + 0.5f) {
				objects.push_back(iterator->second);
			}
			else if (iterator->second->getCenterPos()[0] + iterator->second->getRadius()[0] > i && iterator->second->getCenterPos()[0] + iterator->second->getRadius()[0] < i + 0.5f) {
				objects.push_back(iterator->second);
			}
			else if (iterator->second->getCenterPos()[0] - iterator->second->getRadius()[0] > i && iterator->second->getCenterPos()[0] - iterator->second->getRadius()[0] < i + 0.5f) {
				objects.push_back(iterator->second);
			}
			container.objects = &objects;
			possibleCollisions.push_back(container);
			iterator++;
		}
	}

	/*

	//check if objects within y bounds
	//copy possibleCollisions and clear
	std::vector<Container> possibleCollisionsCopy(possibleCollisions);
	possibleCollisions.clear();
	for (int j = 0; j < possibleCollisionsCopy.size(); j++) {
		for (float i = -5.0f; i < 5.0f; i += 0.5f) {
			//initialize container
			possibleCollisionsCopy[j].lowerBoundY = i;
			possibleCollisionsCopy[j].upperBoundY = i + 0.5f;

			std::vector<PhysicsObject*> objects = *possibleCollisionsCopy[j].objects;
			for (int k = 0; k < objects.size(); k++) {

				//check if any part of object falls within bounds
				if (objects[k]->getCenterPos()[1] > i && objects[k]->getCenterPos()[1] < i + 0.5f);
				else if (objects[k]->getCenterPos()[1] + objects[k]->getRadius()[1] > i && objects[k]->getCenterPos()[1] + objects[k]->getRadius()[1] < i + 0.5f);
				else if (objects[k]->getCenterPos()[1] - objects[k]->getRadius()[1] > i && objects[k]->getCenterPos()[1] - objects[k]->getRadius()[1] < i + 0.5f);
				
				//remove object from container if not in bounds
				else {
					objects.erase(objects.begin() + k);
				}
			}
			possibleCollisions.push_back(possibleCollisionsCopy[j]);
		}
	}

	//check if objects within z bounds
	//copy possibleCollisions and clear
	possibleCollisionsCopy = std::vector<Container>(possibleCollisions);
	possibleCollisions.clear();
	for (int j = 0; j < possibleCollisionsCopy.size(); j++) {
		for (float i = -5.0f; i < 5.0f; i += 0.5f) {
			//initialize container
			possibleCollisions[j].lowerBoundZ = i;
			possibleCollisions[j].upperBoundZ = i + 0.5f;

			std::vector<PhysicsObject*> objects = *possibleCollisionsCopy[j].objects;
			for (int k = 0; k < objects.size(); k++) {

				//check if any part of object falls within bounds
				if (objects[k]->getCenterPos()[2] > i && objects[k]->getCenterPos()[2] < i + 0.5f);
				else if (objects[k]->getCenterPos()[2] + objects[k]->getRadius()[2] > i && objects[k]->getCenterPos()[2] + objects[k]->getRadius()[2] < i + 0.5f);
				else if (objects[k]->getCenterPos()[2] - objects[k]->getRadius()[2] > i && objects[k]->getCenterPos()[2] - objects[k]->getRadius()[2] < i + 0.5f);

				//remove object from container if not in bounds
				else {
					objects.erase(objects.begin() + k);
				}
			}
			possibleCollisions.push_back(possibleCollisionsCopy[j]);
		}
	}
	*/

	//remove all containers that do not have at least two objects
	for (int i = 0; i < possibleCollisions.size(); i++) {
		std::vector<PhysicsObject*> objects = *possibleCollisions[i].objects;
		if (objects.size() < 2) {
			possibleCollisions.erase(possibleCollisions.begin() + i);
		}
	}
}


/*
This function takes all objects in the objects vector and checks if actual collisions between objects happened
If a collision occurs adds the pair of objects to collisionMap map
*/
void CollisionHandler::checkCollisions() {
	//local variables for function
	bool isWithinBoundsX = false;
	bool isWithinBoundsY = false;
	bool isWithinBoundsZ = false;
	float posBoundsChecker; //finds bounds of object via addition of radius and centerpos
	float negBoundsChecker; //same as above with subtraction instead for lower bound
	float otherPosBoundsChecker; //does same as above except with object to compare to
	float otherNegBoundsChecker;

	//iterate through all possibleCollision containers
	for (int i = 0; i < possibleCollisions.size(); i++) {

		//iterate through objects within container
		std::vector<PhysicsObject*> objects = *possibleCollisions[i].objects;
		for (int j = 0; j < objects.size(); j++) {

			//check every other object per object
			for (int k = j + 1; k < objects.size(); k++) {

				//check if centerPos.x +- radius.x is within bounds
				posBoundsChecker = objects[j]->getCenterPos()[0] + objects[j]->getRadius()[0];
				negBoundsChecker = objects[j]->getCenterPos()[0] - objects[j]->getRadius()[0];
				otherPosBoundsChecker = objects[k]->getCenterPos()[0] + objects[k]->getRadius()[0];
				otherNegBoundsChecker = objects[k]->getCenterPos()[0] - objects[k]->getRadius()[0];
				if (posBoundsChecker > otherNegBoundsChecker && negBoundsChecker < otherPosBoundsChecker) {
					isWithinBoundsX = true;
				}

				//check if centerPos.y +- radius.y is within bounds
				posBoundsChecker = objects[j]->getCenterPos()[1] + objects[j]->getRadius()[1];
				negBoundsChecker = objects[j]->getCenterPos()[1] - objects[j]->getRadius()[1];
				otherPosBoundsChecker = objects[k]->getCenterPos()[1] + objects[k]->getRadius()[1];
				otherNegBoundsChecker = objects[k]->getCenterPos()[1] - objects[k]->getRadius()[1];
				if (posBoundsChecker > otherNegBoundsChecker && negBoundsChecker < otherPosBoundsChecker) {
					isWithinBoundsY = true;
				}

				//check if centerPos.z +- radius.z is within bounds
				posBoundsChecker = objects[j]->getCenterPos()[2] + objects[j]->getRadius()[2];
				negBoundsChecker = objects[j]->getCenterPos()[2] - objects[j]->getRadius()[2];
				otherPosBoundsChecker = objects[k]->getCenterPos()[2] + objects[k]->getRadius()[2];
				otherNegBoundsChecker = objects[k]->getCenterPos()[2] - objects[k]->getRadius()[2];
				if (posBoundsChecker > otherNegBoundsChecker && negBoundsChecker < otherPosBoundsChecker) {
					isWithinBoundsZ = true;
				}

				//add to collisions map if both objects within bounds
				if (isWithinBoundsX && isWithinBoundsX && isWithinBoundsZ) {
					collisionMap[objects[j]] = objects[k];
				}

				//set bounds checkers to false for next iteration
				isWithinBoundsX = false;
				isWithinBoundsY = false;
				isWithinBoundsZ = false;
			}
		}
	}
}


/*
This funtion resolves all collisions for object pairings in the collisionMap
If the object is static, no functions are performed and objects colliding into that object have velocity inverted
If non-static objects collide, conservation of momentum equations are used
*/
void CollisionHandler::resolveCollsions() {
	//local variables for this function
	PhysicsObject* object1;
	PhysicsObject* object2;

	//allocate memory for collision operations
	float* object1Velocity;
	float* object2Velocity;
	float object1Mass;
	float object2Mass;

	//initialzie iterator to iterate through map of collisions
	std::map<PhysicsObject*, PhysicsObject*>::iterator iterator = collisionMap.begin();

	//while loop to iterate
	while (iterator != collisionMap.end()) {
		object1 = iterator->first;
		object2 = iterator->second;

		//check if first object is static
		if (object1->getObjectType() == PhysicsObject::PHYSICS_STATIC) {
			//find axis of collision
			//This is done by checking the distance between each respective coordinate in the centerPos
			float distX = fabsf(object1->getCenterPos()[0] - object2->getCenterPos()[0]);
			float distY = fabsf(object1->getCenterPos()[1] - object2->getCenterPos()[1]);
			float distZ = fabsf(object1->getCenterPos()[2] - object2->getCenterPos()[2]);

			//check if collision on xz plane
			if (distY > object1->getRadius()[1]) {
				//reduce energy of object
				object2Velocity = object2->getVelocity();
				object2Velocity[0] = percentEnergyRemaining * object2Velocity[0];
				object2Velocity[1] = -percentEnergyRemaining * object2Velocity[1]; //invert y-velocity
				object2Velocity[2] = percentEnergyRemaining * object2Velocity[2];
				object2->setVelocity(object2Velocity);
			}

			//check if collision on yz plane
			if (distX > object1->getRadius()[0]) {
				//reduce energy of object
				object2Velocity = object2->getVelocity();
				object2Velocity[0] = -percentEnergyRemaining * object2Velocity[0]; //invert x-velocity
				object2Velocity[1] = percentEnergyRemaining * object2Velocity[1]; 
				object2Velocity[2] = percentEnergyRemaining * object2Velocity[2];
				object2->setVelocity(object2Velocity);
			}

			//check if collision on xy plane
			if (distZ > object1->getRadius()[2]) {
				//reduce energy of object
				object2Velocity = object2->getVelocity();
				object2Velocity[0] = percentEnergyRemaining * object2Velocity[0];
				object2Velocity[1] = percentEnergyRemaining * object2Velocity[1];
				object2Velocity[2] = -percentEnergyRemaining * object2Velocity[2]; //invert z-velocity
				object2->setVelocity(object2Velocity);
			}
		}

		//check if second object is static
		else if (object2->getObjectType() == PhysicsObject::PHYSICS_STATIC) {
			//find axis of collision
			//This is done by checking the distance between each respective coordinate in the centerPos
			float distX = fabsf(object1->getCenterPos()[0] - object2->getCenterPos()[0]);
			float distY = fabsf(object1->getCenterPos()[1] - object2->getCenterPos()[1]);
			float distZ = fabsf(object1->getCenterPos()[2] - object2->getCenterPos()[2]);

			//check if collision on xz plane
			if (distY > object2->getRadius()[1]) {
				//reduce energy of object
				object1Velocity = object1->getVelocity();
				object1Velocity[0] = percentEnergyRemaining * object1Velocity[0];
				object1Velocity[1] = -percentEnergyRemaining * object1Velocity[1]; //invert y-velocity
				object1Velocity[2] = percentEnergyRemaining * object1Velocity[2];
				object1->setVelocity(object1Velocity);
			}

			//check if collision on yz plane
			if (distX > object2->getRadius()[0]) {
				//reduce energy of object
				object1Velocity = object1->getVelocity();
				object1Velocity[0] = -percentEnergyRemaining * object1Velocity[0]; //invert x-velocity
				object1Velocity[1] = percentEnergyRemaining * object1Velocity[1];
				object1Velocity[2] = percentEnergyRemaining * object1Velocity[2];
				object1->setVelocity(object1Velocity);
			}

			//check if collision on xy plane
			if (distZ > object2->getRadius()[2]) {
				//reduce energy of object
				object1Velocity = object1->getVelocity();
				object1Velocity[0] = percentEnergyRemaining * object1Velocity[0];
				object1Velocity[1] = percentEnergyRemaining * object1Velocity[1];
				object1Velocity[2] = -percentEnergyRemaining * object1Velocity[2]; //invert z-velocity
				object1->setVelocity(object1Velocity);
			}
		}

		//if neither objects are static do normal momentum based collision
		else {
			//store mass and velocity
			object1Mass = object1->getMass();
			object2Mass = object2->getMass();
			object1Velocity = object1->getVelocity();
			object2Velocity = object2->getVelocity();

			//using momentum equations for velocity recalculations
			object1Velocity[0] = object2Mass / object1Mass * object2Velocity[0] * percentEnergyRemaining;
			object1Velocity[1] = object2Mass / object1Mass * object2Velocity[1] * percentEnergyRemaining;
			object1Velocity[2] = object2Mass / object1Mass * object2Velocity[2] * percentEnergyRemaining;

			object2Velocity[0] = object1Mass / object2Mass * object1Velocity[0] * percentEnergyRemaining;
			object2Velocity[1] = object1Mass / object2Mass * object1Velocity[1] * percentEnergyRemaining;
			object2Velocity[2] = object1Mass / object2Mass * object1Velocity[2] * percentEnergyRemaining;

			object1->setVelocity(object1Velocity);
			object2->setVelocity(object2Velocity);
		}

		//increment iterator
		iterator++;
	}
}

//This function does all the handling for collisions calculations
void CollisionHandler::calcCollisions() {
	findPossibleCollisions();
	checkCollisions();
	resolveCollsions();
}
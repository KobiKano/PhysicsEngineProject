#include "../headers/CollisionHandler.h"

static Logger logger = Logger(Logger::debug);

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
considers only x axis from -5.0 to 5.0
takes step of 0.5 per container
*/
void CollisionHandler::findPossibleCollisions() {
	std::map<std::string, PhysicsObject*>::iterator iterator;
	Container container;

	//check if objects within x bounds
	for (float i = -5.0f; i < 5.0f; i += 0.5f) {
		iterator = objectMap->begin();
		//initialize container
		container = Container();
		container.lowerBoundX = i;
		container.upperBoundX = i + 0.5f;
		//while loop to iterate though objectMap
		while (iterator != objectMap->end()) {
			//check if any part of object falls within bounds
			if (iterator->second->getCenterPos()[0] >= i && iterator->second->getCenterPos()[0] <= i + 0.5f) {
				container.objects.push_back(iterator->second);
			}
			else if (iterator->second->getCenterPos()[0] + iterator->second->getRadius()[0] >= i && iterator->second->getCenterPos()[0] + iterator->second->getRadius()[0] <= i + 0.5f) {
				container.objects.push_back(iterator->second);
			}
			else if (iterator->second->getCenterPos()[0] - iterator->second->getRadius()[0] >= i && iterator->second->getCenterPos()[0] - iterator->second->getRadius()[0] <= i + 0.5f) {
				container.objects.push_back(iterator->second);
			}
			else if (i >= iterator->second->getCenterPos()[0] - iterator->second->getRadius()[0] && i <= iterator->second->getCenterPos()[0] + iterator->second->getRadius()[0]) {
				container.objects.push_back(iterator->second);
			}
			iterator++;
		}
		possibleCollisions.push_back(container);
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
		for (int j = 0; j < possibleCollisions[i].objects.size(); j++) {

			//check every other object per object
			for (int k = j + 1; k < possibleCollisions[i].objects.size(); k++) {

				//check if centerPos.x +- radius.x is within bounds
				posBoundsChecker = possibleCollisions[i].objects[j]->getCenterPos()[0] + possibleCollisions[i].objects[j]->getRadius()[0];
				negBoundsChecker = possibleCollisions[i].objects[j]->getCenterPos()[0] - possibleCollisions[i].objects[j]->getRadius()[0];
				otherPosBoundsChecker = possibleCollisions[i].objects[k]->getCenterPos()[0] + possibleCollisions[i].objects[k]->getRadius()[0];
				otherNegBoundsChecker = possibleCollisions[i].objects[k]->getCenterPos()[0] - possibleCollisions[i].objects[k]->getRadius()[0];
				if (posBoundsChecker > otherNegBoundsChecker && negBoundsChecker < otherPosBoundsChecker) {
					isWithinBoundsX = true;
				}

				//check if centerPos.y +- radius.y is within bounds
				posBoundsChecker = possibleCollisions[i].objects[j]->getCenterPos()[1] + possibleCollisions[i].objects[j]->getRadius()[1];
				negBoundsChecker = possibleCollisions[i].objects[j]->getCenterPos()[1] - possibleCollisions[i].objects[j]->getRadius()[1];
				otherPosBoundsChecker = possibleCollisions[i].objects[k]->getCenterPos()[1] + possibleCollisions[i].objects[k]->getRadius()[1];
				otherNegBoundsChecker = possibleCollisions[i].objects[k]->getCenterPos()[1] - possibleCollisions[i].objects[k]->getRadius()[1];
				if (posBoundsChecker > otherNegBoundsChecker && negBoundsChecker < otherPosBoundsChecker) {
					isWithinBoundsY = true;
				}

				//check if centerPos.z +- radius.z is within bounds
				posBoundsChecker = possibleCollisions[i].objects[j]->getCenterPos()[2] + possibleCollisions[i].objects[j]->getRadius()[2];
				negBoundsChecker = possibleCollisions[i].objects[j]->getCenterPos()[2] - possibleCollisions[i].objects[j]->getRadius()[2];
				otherPosBoundsChecker = possibleCollisions[i].objects[k]->getCenterPos()[2] + possibleCollisions[i].objects[k]->getRadius()[2];
				otherNegBoundsChecker = possibleCollisions[i].objects[k]->getCenterPos()[2] - possibleCollisions[i].objects[k]->getRadius()[2];
				if (posBoundsChecker > otherNegBoundsChecker && negBoundsChecker < otherPosBoundsChecker) {
					isWithinBoundsZ = true;
				}

				//add to collisions map if both objects within bounds
				if (isWithinBoundsX && isWithinBoundsY && isWithinBoundsZ) {
					collisionMap[possibleCollisions[i].objects[j]] = possibleCollisions[i].objects[k];
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
	float randomX;
	float randomY;
	float randomZ;

	//allocate memory for force
	float forceMagnitude;
	float forceDirection[3];

	//allocate memory for reposition calculations
	float newPos[3];
	float distance[3];
	float magnitudeDistance;
	float overlap[3];

	//initialzie iterator to iterate through map of collisions
	std::map<PhysicsObject*, PhysicsObject*>::iterator iterator = collisionMap.begin();

	//while loop to iterate
	while (iterator != collisionMap.end()) {
		object1 = iterator->first;
		object2 = iterator->second;

		logger.debugLog("Collision between: " + object1->getName() + " and " + object2->getName() + "\n");

		//check if first object is static
		if (object1->getObjectType() == PhysicsObject::PHYSICS_STATIC) {
			//find axis of collision
			//This is done by checking the distance between each respective coordinate in the centerPos
			float distX = fabsf(object1->getCenterPos()[0] - object2->getCenterPos()[0]);
			float distY = fabsf(object1->getCenterPos()[1] - object2->getCenterPos()[1]);
			float distZ = fabsf(object1->getCenterPos()[2] - object2->getCenterPos()[2]);

			//find random value
			randomX  = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/0.5f) - 0.25f;
			randomY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 0.5f) - 0.25f;
			randomZ = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 0.5f) - 0.25f;

			//check if collision on xz plane
			if (distY > object1->getRadius()[1]) {
				//reduce energy of object
				object2Velocity = object2->getVelocity();
				object2Velocity[0] = percentEnergyRemaining * object2Velocity[0] + randomX;
				object2Velocity[1] = -percentEnergyRemaining * object2Velocity[1] + randomY; //invert y-velocity
				object2Velocity[2] = percentEnergyRemaining * object2Velocity[2] + randomZ;
				object2->setVelocity(object2Velocity);

				//find collision normal force
				forceMagnitude = 0.0f;
				for (int i = 0; i < object2->forces.size(); i++) {
					forceMagnitude += object2->forces[i].magnitude * object2->forces[i].direction[1];
				}
				forceDirection[0] = 0.0f;
				forceDirection[1] = 1.0f;
				forceDirection[2] = 0.0f;
				//add force
				object2->addForce(Force::PHYSICS_COLLISION_NORMAL, forceMagnitude, forceDirection);

				//make sure object position is no longer in static object
				newPos[0] = object2->getCenterPos()[0];
				newPos[1] = object1->getCenterPos()[1] + object1->getRadius()[1] + object2->getRadius()[1];
				newPos[2] = object2->getCenterPos()[2];
				object2->setCenterPos(newPos);
			}

			//check if collision on yz plane
			if (distX > object1->getRadius()[0]) {
				//reduce energy of object
				object2Velocity = object2->getVelocity();
				object2Velocity[0] = -percentEnergyRemaining * object2Velocity[0] + randomX; //invert x-velocity
				object2Velocity[1] = percentEnergyRemaining * object2Velocity[1] + randomY;
				object2Velocity[2] = percentEnergyRemaining * object2Velocity[2] + randomZ;
				object2->setVelocity(object2Velocity);

				//find collision normal force
				forceMagnitude = 0.0f;
				for (int i = 0; i < object2->forces.size(); i++) {
					forceMagnitude += object2->forces[i].magnitude * object2->forces[i].direction[0];
				}
				forceDirection[0] = 1.0f;
				forceDirection[1] = 0.0f;
				forceDirection[2] = 0.0f;
				//add force
				object2->addForce(Force::PHYSICS_COLLISION_NORMAL, forceMagnitude, forceDirection);

				//make sure object position is no longer in static object
				newPos[0] = object1->getCenterPos()[0] + object1->getRadius()[0] + object2->getRadius()[0];
				newPos[1] = object2->getCenterPos()[1];
				newPos[2] = object2->getCenterPos()[2];
				object2->setCenterPos(newPos);
			}

			//check if collision on xy plane
			if (distZ > object1->getRadius()[2]) {
				//reduce energy of object
				object2Velocity = object2->getVelocity();
				object2Velocity[0] = percentEnergyRemaining * object2Velocity[0] + randomX;
				object2Velocity[1] = percentEnergyRemaining * object2Velocity[1] + randomY;
				object2Velocity[2] = -percentEnergyRemaining * object2Velocity[2] + randomZ; //invert z-velocity
				object2->setVelocity(object2Velocity);

				//find collision normal force
				forceMagnitude = 0.0f;
				for (int i = 0; i < object2->forces.size(); i++) {
					forceMagnitude += object2->forces[i].magnitude * object2->forces[i].direction[2];
				}
				forceDirection[0] = 0.0f;
				forceDirection[1] = 0.0f;
				forceDirection[2] = 1.0f;
				//add force
				object2->addForce(Force::PHYSICS_COLLISION_NORMAL, forceMagnitude, forceDirection);

				//make sure object position is no longer in static object
				newPos[0] = object2->getCenterPos()[0];
				newPos[1] = object2->getCenterPos()[1];
				newPos[2] = object1->getCenterPos()[2] + object1->getRadius()[2] + object2->getRadius()[2];
				object2->setCenterPos(newPos);
			}
		}

		//check if second object is static
		else if (object2->getObjectType() == PhysicsObject::PHYSICS_STATIC) {
			//find axis of collision
			//This is done by checking the distance between each respective coordinate in the centerPos
			float distX = fabsf(object1->getCenterPos()[0] - object2->getCenterPos()[0]);
			float distY = fabsf(object1->getCenterPos()[1] - object2->getCenterPos()[1]);
			float distZ = fabsf(object1->getCenterPos()[2] - object2->getCenterPos()[2]);

			//find random value
			randomX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 0.5f) - 0.25f;
			randomY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 0.5f) - 0.25f;
			randomZ = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 0.5f) - 0.25f;

			//check if collision on xz plane
			if (distY > object2->getRadius()[1]) {
				//reduce energy of object
				object1Velocity = object1->getVelocity();
				object1Velocity[0] = percentEnergyRemaining * object1Velocity[0] + randomX;
				object1Velocity[1] = -percentEnergyRemaining * object1Velocity[1] + randomY; //invert y-velocity
				object1Velocity[2] = percentEnergyRemaining * object1Velocity[2] + randomZ;
				object1->setVelocity(object1Velocity);

				//find collision normal force
				forceMagnitude = 0.0f;
				for (int i = 0; i < object1->forces.size(); i++) {
					forceMagnitude += object1->forces[i].magnitude * object1->forces[i].direction[1];
				}
				forceDirection[0] = 0.0f;
				forceDirection[1] = 1.0f;
				forceDirection[2] = 0.0f;
				//add force
				object1->addForce(Force::PHYSICS_COLLISION_NORMAL, forceMagnitude, forceDirection);

				//make sure object position is no longer in static object
				newPos[0] = object1->getCenterPos()[0];
				newPos[1] = object2->getCenterPos()[1] + object2->getRadius()[1] + object1->getRadius()[1];
				newPos[2] = object1->getCenterPos()[2];
				object1->setCenterPos(newPos);
			}

			//check if collision on yz plane
			if (distX > object2->getRadius()[0]) {
				//reduce energy of object
				object1Velocity = object1->getVelocity();
				object1Velocity[0] = -percentEnergyRemaining * object1Velocity[0] + randomX; //invert x-velocity
				object1Velocity[1] = percentEnergyRemaining * object1Velocity[1] + randomY;
				object1Velocity[2] = percentEnergyRemaining * object1Velocity[2] + randomZ;
				object1->setVelocity(object1Velocity);

				//find collision normal force
				forceMagnitude = 0.0f;
				for (int i = 0; i < object1->forces.size(); i++) {
					forceMagnitude += object1->forces[i].magnitude * object1->forces[i].direction[0];
				}
				forceDirection[0] = 1.0f;
				forceDirection[1] = 0.0f;
				forceDirection[2] = 0.0f;
				//add force
				object1->addForce(Force::PHYSICS_COLLISION_NORMAL, forceMagnitude, forceDirection);

				//make sure object position is no longer in static object
				newPos[0] = object2->getCenterPos()[0] + object2->getRadius()[0] + object1->getRadius()[0];
				newPos[1] = object1->getCenterPos()[1];
				newPos[2] = object1->getCenterPos()[2];
				object1->setCenterPos(newPos);
			}

			//check if collision on xy plane
			if (distZ > object2->getRadius()[2]) {
				//reduce energy of object
				object1Velocity = object1->getVelocity();
				object1Velocity[0] = percentEnergyRemaining * object1Velocity[0] + randomX;
				object1Velocity[1] = percentEnergyRemaining * object1Velocity[1] + randomY;
				object1Velocity[2] = -percentEnergyRemaining * object1Velocity[2] + randomZ; //invert z-velocity
				object1->setVelocity(object1Velocity);

				//find collision normal force
				forceMagnitude = 0.0f;
				for (int i = 0; i < object1->forces.size(); i++) {
					forceMagnitude += object1->forces[i].magnitude * object1->forces[i].direction[2];
				}
				forceDirection[0] = 0.0f;
				forceDirection[1] = 0.0f;
				forceDirection[2] = 1.0f;
				//add force
				object1->addForce(Force::PHYSICS_COLLISION_NORMAL, forceMagnitude, forceDirection);

				//make sure object position is no longer in static object
				newPos[0] = object1->getCenterPos()[0];
				newPos[1] = object1->getCenterPos()[1];
				newPos[2] = object2->getCenterPos()[2] + object2->getRadius()[2] + object1->getRadius()[2];
				object1->setCenterPos(newPos);
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

			//make sure objects no longer overlap
			//find distance between center points
			distance[0] = object2->getCenterPos()[0] - object1->getCenterPos()[0];  //points from object 1 to object 2
			distance[1] = object2->getCenterPos()[1] - object1->getCenterPos()[1];
			distance[2] = object2->getCenterPos()[2] - object1->getCenterPos()[2];

			//check if distance is zero
			magnitudeDistance = sqrtf(powf(distance[0], 2) + powf(distance[1], 2) + powf(distance[2], 2));
			if (magnitudeDistance == 0.0f) {
				//set new pos for object 1
				newPos[0] = object1->getCenterPos()[0] + object2->getRadius()[0];
				newPos[1] = object1->getCenterPos()[1] + object2->getRadius()[1];
				newPos[2] = object1->getCenterPos()[2] + object2->getRadius()[2];
				object1->setCenterPos(newPos);

				//set new pos for object 2
				newPos[0] = object2->getCenterPos()[0] + object1->getRadius()[0];
				newPos[1] = object2->getCenterPos()[1] + object1->getRadius()[1];
				newPos[2] = object2->getCenterPos()[2] + object1->getRadius()[2];
				object2->setCenterPos(newPos);

				//go to next iteration of loop
				continue;
			}

			//find relative overlap x
			if (distance[0] > 0.0f) {
				overlap[0] = -fabsf((object1->getCenterPos()[0] + object1->getRadius()[0]) - (object2->getCenterPos()[0] - object2->getRadius()[0]));
			}
			else {
				overlap[0] = fabsf((object2->getCenterPos()[0] + object2->getRadius()[0]) - (object1->getCenterPos()[0] - object1->getRadius()[0]));
			}

			//find relative overlap y
			if (distance[1] > 0.0f) {
				overlap[1] = -fabsf((object1->getCenterPos()[1] + object1->getRadius()[1]) - (object2->getCenterPos()[1] - object2->getRadius()[1]));
			}
			else {
				overlap[1] = fabsf((object2->getCenterPos()[1] + object2->getRadius()[1]) - (object1->getCenterPos()[1] - object1->getRadius()[1]));
			}

			//find relative overlap z
			if (distance[2] > 0.0f) {
				overlap[2] = -fabsf((object1->getCenterPos()[2] + object1->getRadius()[2]) - (object2->getCenterPos()[2] - object2->getRadius()[2]));
			}
			else {
				overlap[2] = fabsf((object2->getCenterPos()[2] + object2->getRadius()[2]) - (object1->getCenterPos()[2] - object1->getRadius()[2]));
			}

			//calculate new position
			newPos[0] = object1->getCenterPos()[0] + overlap[0] / 2;
			newPos[1] = object1->getCenterPos()[1] + overlap[1] / 2;
			newPos[2] = object1->getCenterPos()[2] + overlap[2] / 2;
			object1->setCenterPos(newPos);

			newPos[0] = object2->getCenterPos()[0] - overlap[0] / 2;
			newPos[1] = object2->getCenterPos()[1] - overlap[1] / 2;
			newPos[2] = object2->getCenterPos()[2] - overlap[2] / 2;
			object2->setCenterPos(newPos);
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

//this function resets all fields within the class
void CollisionHandler::resetFields() {
	possibleCollisions.clear();
	collisionMap.clear();
}
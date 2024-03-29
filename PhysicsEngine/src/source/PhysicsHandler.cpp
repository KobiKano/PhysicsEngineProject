#include "../headers/PhysicsHandler.h"
//initialize logger
static Logger logger = Logger(Logger::info);

//this is the constructor for this class
PhysicsHandler::PhysicsHandler(PhysicsObject* currObject,  float deltaTime, float airResistance) {
	this->currObject = currObject;
	this->airResistance = airResistance;
	findForces();
	calcAcceration();
	calcVelocity(deltaTime);
	calcPosition(deltaTime);

	if (isRotational) {
		addNewRotationalForce();
	}

	//set new values in currObject
	currObject->setCenterPos(nextPos);
	currObject->setVelocity(velocity);
}

//this function calculates the new rotational force
void PhysicsHandler::addNewRotationalForce() {
	float direction[3] = { -nextPos[0], -nextPos[1], -nextPos[2] };

	//add force
	currObject->addForce(Force::PHYSICS_ROTATIONAL, rotationalMagnitude, direction);
}

//this is a private function that finds all forces on the currObject
void PhysicsHandler::findForces() {
	rotationalMagnitude = 0.0f;
	for (int i = 0; i < currObject->forces.size(); i++) {
		forces.x += currObject->forces[i].magnitude * currObject->forces[i].direction[0];
		//logger.debugLog("direction.x = " + std::to_string(currObject->forces[i].direction[0]) + "\n");
		forces.y += currObject->forces[i].magnitude * currObject->forces[i].direction[1];
		//logger.debugLog("direction.y = " + std::to_string(currObject->forces[i].direction[1]) + "\n");
		forces.z += currObject->forces[i].magnitude * currObject->forces[i].direction[2];
		//logger.debugLog("direction.z = " + std::to_string(currObject->forces[i].direction[2]) + "\n");

		//check if force is frictional force
		if (currObject->forces[i].forceType == Force::PHYSICS_FRICTION) {
			currObject->forces.erase(std::vector<Force>::iterator(currObject->forces.begin() + i));
			i--;
		}

		//check if force is rotational
		if (currObject->forces[i].forceType == Force::PHYSICS_ROTATIONAL) {
			rotationalMagnitude += currObject->forces[i].magnitude;
			isRotational = true;
			currObject->forces.erase(std::vector<Force>::iterator(currObject->forces.begin() + i));
			i--;
		}
	}
	//logger.debugLog("forces.x = " + std::to_string(forces.x) + "\n");
	//logger.debugLog("forces.y = " + std::to_string(forces.y) + "\n");
	//logger.debugLog("forces.z = " + std::to_string(forces.z) + "\n");
}

//this function uses the forces and the mass field of currObject to calculate acceleration
void PhysicsHandler::calcAcceration() {
	float mass = currObject->getMass();
	acceleration.x = forces.x / mass;
	acceleration.y = forces.y / mass;
	acceleration.z = forces.z / mass;
	//logger.debugLog("acceleration.x = " + std::to_string(acceleration.x) + "\n");
	//logger.debugLog("acceleration.y = " + std::to_string(acceleration.y) + "\n");
	//logger.debugLog("accelereation.z = " + std::to_string(acceleration.z) + "\n\n");
}

//this function uses the calculated acceleration and past velocity to calculate the new velocity
void PhysicsHandler::calcVelocity(float deltaTime) {
	float* currVelocity = currObject->getVelocity();
	float velocityMagnitude;
	float forceMagnitude;
	float forceDirection[3];
	velocity[0] = currVelocity[0] + acceleration.x * deltaTime;
	velocity[1] = currVelocity[1] + acceleration.y * deltaTime;
	velocity[2] = currVelocity[2] + acceleration.z * deltaTime;

	//add new air resistance forces based on new velocity
	velocityMagnitude = sqrtf(powf(velocity[0], 2) + powf(velocity[1], 2) + powf(velocity[2], 2));
	//check if velocity magnitude is really small, if so set to zero to avoid weird artifacts
	if (velocityMagnitude >= 0.1) {
		forceMagnitude = 0.5f * powf(velocityMagnitude, 2) * airResistance * powf(currObject->getRadius()[0], 2);
		//normalize force direction to opposite direction of velocity
		forceDirection[0] = -velocity[0] / velocityMagnitude;
		forceDirection[1] = -velocity[1] / velocityMagnitude;
		forceDirection[2] = -velocity[2] / velocityMagnitude;

		currObject->addForce(Force::PHYSICS_FRICTION, forceMagnitude, forceDirection);
	}
	else {
		velocity[0] = 0.0f;
		velocity[1] = 0.0f;
		velocity[2] = 0.0f;
	}

	logger.debugLog("velocity.x = " + std::to_string(velocity[0]) + "\n");
	logger.debugLog("velocity.y = " + std::to_string(velocity[1]) + "\n");
	logger.debugLog("velocity.z = " + std::to_string(velocity[2]) + "\n\n");
}

//this is a private function that uses the forces to calculate the new position
void PhysicsHandler::calcPosition(float deltaTime) {
	float* currPosition = currObject->getCenterPos();
	float* currVelocity = currObject->getVelocity();
	nextPos[0] = currPosition[0] + currVelocity[0] * deltaTime + 0.5 * acceleration.x * powf(deltaTime, 2);
	nextPos[1] = currPosition[1] + currVelocity[1] * deltaTime + 0.5 * acceleration.y * powf(deltaTime, 2);
	nextPos[2] = currPosition[2] + currVelocity[2] * deltaTime + 0.5 * acceleration.z * powf(deltaTime, 2);

	//logger.debugLog("position.x = " + std::to_string(nextPos[0]) + "\n");
	//logger.debugLog("position.y = " + std::to_string(nextPos[1]) + "\n");
	//logger.debugLog("position.z = " + std::to_string(nextPos[2]) + "\n\n");
}

//this function returns the new position
float* PhysicsHandler::getNextPos() {
	return nextPos;
}
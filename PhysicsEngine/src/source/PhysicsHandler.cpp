#include "../headers/PhysicsHandler.h"
//initialize logger
static Logger logger = Logger(Logger::debug);

//this is the constructor for this class
PhysicsHandler::PhysicsHandler(PhysicsObject* currObject,  float deltaTime) {
	findForces(currObject);
	calcAcceration(currObject);
	calcVelocity(currObject, deltaTime);
	calcPosition(currObject, deltaTime);

	//set new values in currObject
	currObject->setCenterPos(nextPos);
	currObject->setVelocity(velocity);
}

//this is a private function that finds all forces on the currObject
void PhysicsHandler::findForces(PhysicsObject* currObject) {
	for (int i = 0; i < currObject->forces.size(); i++) {
		forces.x += currObject->forces[i].magnitude * currObject->forces[i].direction[0];
		logger.debugLog("direction.x = " + std::to_string(currObject->forces[i].direction[0]) + "\n");
		forces.y += currObject->forces[i].magnitude * currObject->forces[i].direction[1];
		logger.debugLog("direction.y = " + std::to_string(currObject->forces[i].direction[1]) + "\n");
		forces.z += currObject->forces[i].magnitude * currObject->forces[i].direction[2];
		logger.debugLog("direction.z = " + std::to_string(currObject->forces[i].direction[2]) + "\n");
	}
	logger.debugLog("forces.x = " + std::to_string(forces.x) + "\n");
	logger.debugLog("forces.y = " + std::to_string(forces.y) + "\n");
	logger.debugLog("forces.z = " + std::to_string(forces.z) + "\n");
}

//this function uses the forces and the mass field of currObject to calculate acceleration
void PhysicsHandler::calcAcceration(PhysicsObject* currObject) {
	float mass = currObject->getMass();
	acceleration.x = forces.x / mass;
	acceleration.y = forces.y / mass;
	acceleration.z = forces.z / mass;
	logger.debugLog("acceleration.x = " + std::to_string(acceleration.x) + "\n");
	logger.debugLog("acceleration.y = " + std::to_string(acceleration.y) + "\n");
	logger.debugLog("accelereation.z = " + std::to_string(acceleration.z) + "\n\n");
}

//this function uses the calculated acceleration and past velocity to calculate the new velocity
void PhysicsHandler::calcVelocity(PhysicsObject* currObject, float deltaTime) {
	float* currVelocity = currObject->getVelocity();
	velocity[0] = currVelocity[0] + acceleration.x * deltaTime;
	velocity[1] = currVelocity[1] + acceleration.y * deltaTime;
	velocity[2] = currVelocity[2] + acceleration.z * deltaTime;

	logger.debugLog("velocity.x = " + std::to_string(velocity[0]) + "\n");
	logger.debugLog("velocity.y = " + std::to_string(velocity[1]) + "\n");
	logger.debugLog("velocity.z = " + std::to_string(velocity[2]) + "\n\n");
}

//this is a private function that uses the forces to calculate the new position
void PhysicsHandler::calcPosition(PhysicsObject* currObject, float deltaTime) {
	float* currPosition = currObject->getCenterPos();
	float* currVelocity = currObject->getVelocity();
	nextPos[0] = currPosition[0] + currVelocity[0] * deltaTime + 0.5 * acceleration.x * powf(deltaTime, 2);
	nextPos[1] = currPosition[1] + currVelocity[1] * deltaTime + 0.5 * acceleration.y * powf(deltaTime, 2);
	nextPos[2] = currPosition[2] + currVelocity[2] * deltaTime + 0.5 * acceleration.z * powf(deltaTime, 2);

	logger.debugLog("position.x = " + std::to_string(nextPos[0]) + "\n");
	logger.debugLog("position.y = " + std::to_string(nextPos[1]) + "\n");
	logger.debugLog("position.z = " + std::to_string(nextPos[2]) + "\n\n");
}

//this function returns the new position
float* PhysicsHandler::getNextPos() {
	return nextPos;
}
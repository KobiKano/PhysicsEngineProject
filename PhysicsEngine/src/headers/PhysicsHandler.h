#pragma once

#include "Engine.h"
#include "PhysicsObject.h"
#include <string>

//generic vec3 struct
struct vec3 {
	float x = 0.0f, y = 0.0f, z = 0.0f;
};

//this class handles all physics position calculations
class PhysicsHandler {
	//private fields of this class
	float airResistance;
	vec3 forces;
	float nextPos[3];
	float velocity[3];
	vec3 acceleration;

	//private functions of this class
	void findForces(PhysicsObject* currObject);
	void calcAcceration(PhysicsObject* currObject);
	void calcVelocity(PhysicsObject* currObject, float deltaTime);
	void calcPosition(PhysicsObject* currObject, float deltaTime);
public:
	//constructor for this class
	PhysicsHandler(PhysicsObject* currObject, float deltaTime, float airResistance);

	//functions for this class
	float* getNextPos();
};

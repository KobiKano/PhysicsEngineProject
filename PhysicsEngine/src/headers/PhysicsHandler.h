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
	PhysicsObject* currObject;
	float airResistance;
	vec3 forces;
	float nextPos[3];
	float velocity[3];
	vec3 acceleration;
	bool isRotational = false;
	float rotationalMagnitude;

	//private functions of this class
	void findForces();
	void calcAcceration();
	void calcVelocity(float deltaTime);
	void calcPosition(float deltaTime);
	void addNewRotationalForce();
public:
	//constructor for this class
	PhysicsHandler(PhysicsObject* currObject, float deltaTime, float airResistance);

	//functions for this class
	float* getNextPos();
};

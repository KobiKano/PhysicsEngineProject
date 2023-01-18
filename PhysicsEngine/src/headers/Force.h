#pragma once

//this struct stores all information for a given force
struct Force {
	//fields for this class
	enum ForceType {
		PHYSICS_GRAVITATIONAL = 0, PHYSICS_SPRING, PHYSICS_NORMAL, PHYSICS_FRICTION, PHYSICS_IMPULSE, PHYSICS_COLLISION_NORMAL
	};
	float magnitude;
	float direction[3];
	ForceType forceType;

	//constructor for this class
	Force(ForceType forceType, float magnitude, float direction[3]);
};

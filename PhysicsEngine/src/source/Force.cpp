#include "../headers/Force.h"

Force::Force(ForceType forceType, float magnitude, float direction[3]) {
	this->forceType = forceType;
	this->magnitude = magnitude;
	this->direction[0] = direction[0];
	this->direction[1] = direction[1];
	this->direction[2] = direction[2];
}
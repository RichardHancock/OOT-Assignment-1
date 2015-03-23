#include "stdafx.h"
#include "Helicopter.h"

#include <math.h>

#include "Util.h"

Helicopter::Helicopter(Ogre::Vector3 pos) 
	: EntityWithMotion(pos)
{
	classType = "Helicopter";
}

Helicopter::~Helicopter() { }

void Helicopter::setRotorSpeed(float mainRotorSpeed, float aftRotorSpeed)
{
	this->mainRotorSpeed = mainRotorSpeed;
	this->aftRotorSpeed = aftRotorSpeed;
}

void Helicopter::update(float dt)
{
	Util::applyDrag(vel, 0.40f);
	pos += vel * dt;
	
	Entity::update(dt);

	updateRotors(dt);
}

void Helicopter::updateRotors(float dt)
{
	float angle = mainRotorSpeed * Ogre::Math::PI / 180.0f * dt;
	mainRotorNode->rotate(Ogre::Quaternion(Util::RotationMatrixXYZ(Ogre::Vector3(0, 0, angle))), Ogre::Node::TS_LOCAL);
	
	angle = aftRotorSpeed * Ogre::Math::PI / 180.0f * dt;
	aftRotorNode->rotate(Ogre::Quaternion(Util::RotationMatrixXYZ(Ogre::Vector3(angle, 0, 0))), Ogre::Node::TS_LOCAL);
}
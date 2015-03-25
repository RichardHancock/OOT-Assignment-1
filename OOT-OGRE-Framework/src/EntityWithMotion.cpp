#include "stdafx.h"
#include "EntityWithMotion.h"
#include "Util.h"

EntityWithMotion::EntityWithMotion(Ogre::Vector3 pos, float maxSpeed)
	: Entity(pos), maxSpeed(maxSpeed)
{
	classType = "EntityWithMotion";
	vel = 0;
}

EntityWithMotion::~EntityWithMotion()
{

}


void EntityWithMotion::setVelocity(Ogre::Vector3 newVel)
{
	if (newVel.x <= maxSpeed && newVel.y <= maxSpeed && newVel.z <= maxSpeed &&
		newVel.x >= -maxSpeed && newVel.y >= -maxSpeed && newVel.z >= -maxSpeed)
	{
		vel = newVel;
	}
}

void EntityWithMotion::increaseVelocity(Ogre::Vector3 increase)
{
	//Increases velocity by input unless greater than the max speed
	vel += increase;
	Util::keepInBounds(vel, maxSpeed);
}
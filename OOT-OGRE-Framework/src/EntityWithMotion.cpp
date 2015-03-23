#include "stdafx.h"
#include "EntityWithMotion.h"

EntityWithMotion::EntityWithMotion(Ogre::Vector3 pos)
	: Entity(pos)
{
	classType = "EntityWithMotion";
	vel = 0;
}

EntityWithMotion::~EntityWithMotion()
{

}


void EntityWithMotion::setVelocity(Ogre::Vector3 newVel)
{
	vel = newVel;
}

void EntityWithMotion::increaseVelocity(Ogre::Vector3 increase)
{
	vel += increase;
}
#pragma once

#include "stdafx.h"

#include <memory>

#include "Entity.h"
#include "OgreApplication.h"

class EntityWithMotion : public Entity
{
public:
	EntityWithMotion(Ogre::Vector3 pos, float maxSpeed);

	virtual ~EntityWithMotion();

	void setVelocity(Ogre::Vector3 newVel);

	void increaseVelocity(Ogre::Vector3 increase);

protected:

	Ogre::Vector3 vel;

	///Maximum speed of the entity
	const float maxSpeed;
};
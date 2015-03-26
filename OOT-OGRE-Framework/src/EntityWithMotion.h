#pragma once

#include "stdafx.h"

#include <memory>

#include "Entity.h"
#include "OgreApplication.h"

/**
@class EntityWithMotion
@brief An Entity with a Velocity
*/
class EntityWithMotion : public Entity
{
public:
	/**
	@brief Create EntityWithMotion
	@param Ogre::Vector3 - Starting Position
	@param float - Maximum speed in all directions
	*/
	EntityWithMotion(Ogre::Vector3 pos, float maxSpeed);

	virtual ~EntityWithMotion();

	/**
	@brief Sets the Entity's current velocity
	@param Ogre::Vector3 - New Velocity
	*/
	void setVelocity(Ogre::Vector3 newVel);

	/**
	@brief Increases the Entity's current velocity by the passed in Vector 3
	@param Ogre::Vector3 - Velocity increase amount
	*/
	void increaseVelocity(Ogre::Vector3 increase);

protected:

	///Entity's current velocity
	Ogre::Vector3 vel;

	///Maximum speed of the entity
	const float maxSpeed;
};
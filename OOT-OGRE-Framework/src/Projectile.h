#pragma once

#include "stdafx.h"

#include "EntityWithMotion.h"
#include "Util.h"

/**
@class Projectile
@brief A projectile with basic constant acceleration projectile motion
*/
class Projectile : public EntityWithMotion
{
public:
	/**
	@brief Create Projectile
	@param Ogre::Vector3 - Starting Position
	*/
	Projectile(Ogre::Vector3 pos);

	virtual ~Projectile();

	/**
	@brief Update Internal values
	@param float - Delta time
	*/
	virtual void update(float dt);

	/**
	@brief Fire the projectile along the passed in direction
	@param Ogre::Vector3 - Launch vector
	@param float - Gravity influence
	*/
	void fire(Ogre::Vector3 fireVelocity, float gravity);

	/**
	@brief Has the bullet reached the end of its lifespan
	@return bool - True if expired, else false
	*/
	bool expired();

private:
	
	///Has the bullet been fired 
	bool fired;

	///The force of gravity acting on the projectile
	float gravity;

	///Timer keeping track of the projectiles lifespan
	Util::Timer lifespan;

};
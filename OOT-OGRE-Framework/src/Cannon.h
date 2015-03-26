#pragma once

#include "stdafx.h"
#include "Entity.h"
#include "Projectile.h"
#include "Util.h"

/**
@class Cannon
@brief A Cannon that can fire projectiles at a target
*/
class Cannon : public Entity
{
public:
	/**
	@brief Create Cannon
	@param Ogre::Vector3 - Starting Position
	*/
	Cannon(Ogre::Vector3 pos);

	virtual ~Cannon();
	
	/**
	@brief Update Internal values
	@param float - Delta time
	*/
	virtual void update(float dt);

	/**
	@brief Rotate the cannon towards the target, also updates the direction vec3
	@param Ogre::Vector3 - The target position
	*/
	void aim(Ogre::Vector3 targetPos);

	/**
	@brief Fire the cannon at the current direction vector. Only Fires if the reloadDelay has finished.
	@return shared_ptr<Projectile> - The fired bullet
	*/
	shared_ptr<Projectile> fire();

	/**
	@brief Returns the remaining time before the cannon can be fired again
	@return float - Time remaining in seconds (Not Rounded)
	*/
	float getRemainingReloadTime() { return reloadDelay.getTimeRemaining(); };

protected:

	///Target position from the previous aim function call
	Ogre::Vector3 targetPrevPos;

	///Is this the first run of the cannon code (Uses some special behavior since there is no targetPrevPos yet)
	bool firstRun;

	///Direction towards the target, used for firing the projectiles
	Ogre::Vector3 direction;

	///Timer used to create a delay between cannon firings
	Util::Timer reloadDelay;
};
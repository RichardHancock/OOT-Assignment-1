#pragma once

#include "stdafx.h"

#include "EntityWithMotion.h"
#include "Util.h"

class Projectile : public EntityWithMotion
{
public:
	Projectile(Ogre::Vector3 pos);

	virtual ~Projectile();

	virtual void update(float dt);

	void fire(Ogre::Vector3 fireVelocity, float gravity);

	bool expired();

private:
	
	bool fired;

	float gravity;

	Util::Timer lifespan;
};
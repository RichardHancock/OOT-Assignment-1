#pragma once

#include "stdafx.h"

#include "EntityWithMotion.h"

class Projectile : public EntityWithMotion
{
public:
	Projectile(Ogre::Vector3 pos);

	virtual ~Projectile();

	virtual void update(float dt);

	void fire(Ogre::Vector3 initVel, float gravity);

private:
	

	bool fired;

	///The Initial velocity of the projectile
	Ogre::Vector3 initVel;

	///The Initial position of the projectile
	Ogre::Vector3 initPos;

	float gravity;
};
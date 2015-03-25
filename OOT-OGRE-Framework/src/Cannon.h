#pragma once

#include "stdafx.h"
#include "Entity.h"
#include "Projectile.h"

class Cannon : public Entity
{
public:
	Cannon(Ogre::Vector3 pos);

	virtual ~Cannon();

	virtual void update(float dt);

	void aim(Ogre::Vector3 targetPos);

	Projectile fire();

protected:

	Ogre::Vector3 targetPrevPos;

	bool firstRun;

	Ogre::Vector3 direction;
};
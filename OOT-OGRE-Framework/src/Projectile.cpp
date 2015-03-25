#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile(Ogre::Vector3 pos)
	: EntityWithMotion(pos, 200.0f)
{
	classType = "Projectile";

	fired = false;
	gravity = 0;
}

Projectile::~Projectile()
{

}

void Projectile::update(float dt)
{
	lifespan.update(dt);
	
	if (fired)
	{
		vel.y -= gravity * dt;
	
		pos += vel * dt;

	}
	

	Entity::update(dt);
}

void Projectile::fire(Ogre::Vector3 fireVelocity, float gravity)
{
	this->vel = fireVelocity;
	fired = true;

	this->gravity = gravity;

	lifespan.reset(20.0f);
}

bool Projectile::expired()
{
	//If the projectile has been fired and its timer ran out it is expired
	return (fired && lifespan.hasTimerFinished());
}
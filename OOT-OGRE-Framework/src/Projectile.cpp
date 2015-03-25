#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile(Ogre::Vector3 pos)
	: EntityWithMotion(pos)
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

	
}
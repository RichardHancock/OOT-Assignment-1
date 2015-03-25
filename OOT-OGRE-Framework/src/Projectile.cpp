#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile(Ogre::Vector3 pos)
	: EntityWithMotion(pos)
{
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
		
	}
}

void Projectile::fire(Ogre::Vector3 initVel, float gravity)
{
	vel, this->initVel = initVel;


	
}
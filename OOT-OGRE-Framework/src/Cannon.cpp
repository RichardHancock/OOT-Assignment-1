#include "stdafx.h"
#include "Cannon.h"

Cannon::Cannon(Ogre::Vector3 pos)
	: Entity(pos)
{
	classType = "Cannon";
	
	direction = 0;
	firstRun = true;
	targetPrevPos = 0.0f;
}

Cannon::~Cannon()
{

}

void Cannon::update(float dt)
{
	reloadDelay.update(dt);
	Entity::update(dt);
}

void Cannon::aim(Ogre::Vector3 targetPos)
{
	if (firstRun)
	{
		targetPrevPos = 0;
		firstRun = false;
	}

	Ogre::Vector3 v1 = (targetPrevPos - pos).normalisedCopy();
	Ogre::Vector3 v2 = (targetPos - pos).normalisedCopy();

	Ogre::Vector3 v3 = (v1.crossProduct(v2)).normalisedCopy();

	Ogre::Radian angle = Ogre::Math::ACos(v1.dotProduct(v2));

	Ogre::Quaternion quat = Ogre::Quaternion(
		Ogre::Math::Cos(0.5 * angle),
		v3.x * Ogre::Math::Sin(0.5 * angle),
		v3.y * Ogre::Math::Sin(0.5 * angle),
		v3.z * Ogre::Math::Sin(0.5 * angle)
		);

	direction = v2;

	//node->setOrientation(quat);
	node->rotate(quat,Ogre::Node::TS_LOCAL);
	
	targetPrevPos = targetPos;
}

shared_ptr<Projectile> Cannon::fire()
{
	if (reloadDelay.hasTimerFinished())
	{
		shared_ptr<Projectile> proj;

		proj = make_shared<Projectile>(pos);

		//Gravity offset to stop the projectile falling short
		direction.y += 0.13f;

		proj->fire(direction * 100, 10.0f);

		//Reset 7 sec delay
		reloadDelay.reset(7.0f);

		return proj;
	}
	else
	{
		return nullptr;
	}
}
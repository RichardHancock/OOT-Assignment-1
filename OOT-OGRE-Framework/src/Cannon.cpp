#include "stdafx.h"
#include "Cannon.h"

Cannon::Cannon(Ogre::Vector3 pos)
	: Entity(pos)
{
	firstRun = true;
	targetPrevPos = 0.0f;
}

Cannon::~Cannon()
{

}

void Cannon::update(float dt)
{

}

void Cannon::aim(Ogre::Vector3 targetPos)
{
	if (firstRun)
	{
		targetPrevPos = targetPos;
		firstRun = false;
	}

	Ogre::Vector3 v1 = (pos - targetPrevPos).normalisedCopy();
	Ogre::Vector3 v2 = (pos - targetPos).normalisedCopy();

	Ogre::Vector3 v3 = v1.crossProduct(v2);

	Ogre::Radian angle = Ogre::Math::ACos(v1.dotProduct(v2));

	Ogre::Quaternion quat = Ogre::Quaternion(
		Ogre::Math::Cos(0.5 * angle),
		v3.x * Ogre::Math::Sin(0.5 * angle),
		v3.y * Ogre::Math::Sin(0.5 * angle),
		v3.z * Ogre::Math::Sin(0.5 * angle)
		);

	direction = v2;

	node->setOrientation(quat);
	targetPrevPos = targetPos;
}

Projectile Cannon::fire()
{
	Projectile proj(pos);

	proj.fire(direction * 10, 1.0f);

	return proj;

}
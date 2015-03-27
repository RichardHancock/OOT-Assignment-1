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
		targetPrevPos = Ogre::Vector3(1,1,1);
		firstRun = false;
	}

	Ogre::Vector3 v1 = (targetPrevPos - pos).normalisedCopy();
	Ogre::Vector3 v2 = (targetPos - pos).normalisedCopy();

	Ogre::Vector3 v3 = (v2.crossProduct(v1)).normalisedCopy();

	Ogre::Radian angle = -Ogre::Math::ACos(v1.dotProduct(v2));

	Ogre::Quaternion quat = Ogre::Quaternion(
		Ogre::Math::Cos(0.5 * angle),
		v3.x * Ogre::Math::Sin(0.5 * angle),
		v3.y * Ogre::Math::Sin(0.5 * angle),
		v3.z * Ogre::Math::Sin(0.5 * angle)
		);

	direction = v2;

	//node->setOrientation(quat);
	node->rotate(quat,Ogre::Node::TS_WORLD);
	
	targetPrevPos = targetPos;
}

shared_ptr<Projectile> Cannon::fire(OgreApplication* app)
{
	if (reloadDelay.hasTimerFinished())
	{
		shared_ptr<Projectile> proj;

		proj = make_shared<Projectile>(pos);

		proj->setActor(app, Ogre::Vector3(0.0f), 0.03f, "sphere.mesh", "floor_diffuse.PNG", nullptr);

		//Gravity offset to stop the projectile falling short
		direction.y += 0.11f;

		proj->fire(direction * 250, 60.0f, app);
		
		//Reset 4 sec delay
		reloadDelay.reset(4.0f);

		return proj;
	}
	else
	{
		return nullptr;
	}
}
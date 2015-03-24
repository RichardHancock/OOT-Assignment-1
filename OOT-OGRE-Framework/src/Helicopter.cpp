#include "stdafx.h"
#include "Helicopter.h"

#include "Util.h"

Helicopter::Helicopter(Ogre::Vector3 pos) 
	: EntityWithMotion(pos)
{
	classType = "Helicopter";
	rotationSpeed = 0.0f;
}

Helicopter::~Helicopter() { }

void Helicopter::setActor(OgreApplication* app, float angle, float scale, 
	std::string meshFile, std::string textureFile, Ogre::SceneNode* parent)
{
	Entity::setActor(app, angle, scale, meshFile, textureFile, parent);

	Rotor* tempMainRotor = new Rotor(Ogre::Vector3(0.0f, 0.0f, -0.045f), 
		720, Ogre::Vector3(0,0,1));

	tempMainRotor->setActor(app,0,1,"topRotor.mesh", "green.png", node.get());

	mainRotor.reset(tempMainRotor);

	Rotor* tempAftRotor = new Rotor(Ogre::Vector3(-0.015f, -0.11f, -0.004f), 
		720, Ogre::Vector3(1,0,0));

	tempAftRotor->setActor(app,0,1,"aftRotor.mesh", "green.png", node.get());
	
	aftRotor.reset(tempAftRotor);
}

void Helicopter::update(float dt)
{
	Util::applyDrag(vel, 0.50f);
	pos += vel * dt;

	if (rotationSpeed != 0.00f)
	{
		std::cout << "Before: " << rotationSpeed;
		Util::applyDrag(rotationSpeed, 0.40f);
		std::cout << ", After: " << rotationSpeed << std::endl;
		//Ogre::Vector3 rotation(0.0f, 0.0f, rotationSpeed * dt);
		node->roll(Ogre::Radian(rotationSpeed * dt));
		//node->rotate(Util::rotate_z(rotationSpeed * dt));
		//rotationSpeed = 0;
	}


	Entity::update(dt);

	mainRotor->setSpeedPercent(100);
	aftRotor->setSpeedPercent(100);

	mainRotor->update(dt);
	aftRotor->update(dt);
	
	
}

void Helicopter::increaseRotatationSpeed(float speed)
{
	rotationSpeed += speed;
}
#include "stdafx.h"
#include "Helicopter.h"

#include "Util.h"



Helicopter::Helicopter(Ogre::Vector3 pos, float maxSpeed) 
	: EntityWithMotion(pos, maxSpeed), maxRotationSpeed(3.0f)
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
		1080, Ogre::Vector3(0,0,1));

	tempMainRotor->setActor(app,0,1,"topRotor.mesh", "green.png", node.get());

	mainRotor.reset(tempMainRotor);

	Rotor* tempAftRotor = new Rotor(Ogre::Vector3(-0.015f, -0.11f, -0.004f), 
		1080, Ogre::Vector3(1,0,0));

	tempAftRotor->setActor(app,0,1,"aftRotor.mesh", "green.png", node.get());
	
	aftRotor.reset(tempAftRotor);

	mainRotor->setSpeedPercent(30);
	aftRotor->setSpeedPercent(30);
}

void Helicopter::update(float dt)
{
	Util::applyDrag(vel, 0.70f);
	
	node->translate(vel * dt, Ogre::Node::TS_LOCAL);

	pos = node->getPosition();

	if (rotationSpeed != 0.00f)
	{
		Util::applyDrag(rotationSpeed, 0.40f);
		node->roll(Ogre::Radian(rotationSpeed * dt));
	}

	calculateRotorSpeed(mainRotor.get(), vel.z, maxSpeed);
	calculateRotorSpeed(aftRotor.get(), rotationSpeed, maxRotationSpeed);

	mainRotor->update(dt);
	aftRotor->update(dt);
	
}

void Helicopter::increaseRotatationSpeed(float speed)
{
	//Adds the input to the rotation speed
	//sets it to the max speed if rotation speed is too fast
	rotationSpeed += speed;
	Util::keepInBounds(rotationSpeed, maxRotationSpeed);
}

void Helicopter::handleInput(OIS::Keyboard* keyboard)
{

	//Propulsion (Forward/Back)
	if (keyboard->isKeyDown(OIS::KC_W))
	{
		increaseVelocity(Ogre::Vector3(0, 1.0f, 0));
	}
	else if (keyboard->isKeyDown(OIS::KC_S))
	{
		increaseVelocity(Ogre::Vector3(0, -1.0f, 0));
	}

	// Strafe (Move Left/ Move Right)
	if (keyboard->isKeyDown(OIS::KC_A))
	{
		increaseVelocity(Ogre::Vector3(1.0f, 0, 0));
	}
	else if (keyboard->isKeyDown(OIS::KC_D))
	{
		increaseVelocity(Ogre::Vector3(-1.0f, 0, 0));
	}

	//Altitude (Up/ Down)
	if (keyboard->isKeyDown(OIS::KC_LSHIFT))
	{
		increaseVelocity(Ogre::Vector3(0, 0, -1.0f));
	}
	else if (keyboard->isModifierDown(OIS::Keyboard::Alt))
	{
		increaseVelocity(Ogre::Vector3(0, 0, 1.0f));
	}

	//Yaw (Turn Left/Right)
	if (keyboard->isKeyDown(OIS::KC_Q))
	{
		increaseRotatationSpeed(-0.25f);
	}
	else if (keyboard->isKeyDown(OIS::KC_E))
	{
		increaseRotatationSpeed(0.25f);
	}
}

void Helicopter::calculateRotorSpeed(Rotor* rotor, float speed, float maximumSpeed)
{
	/*
		This calculates the rotation speed of the rotors. The main rotor is affected by
		up and down velocity, while the aft rotor is affected by rotations.
		The rotors will always been spinning a reasonable amount (30%) for realism.
		This means the scale is between 0-70%, 35% being the idle state (no velocity just 
		hovering). Once this percentage has been calculated the minimum rotor rotation speed 
		is added to it, which gives the final speed percentage for the rotor.
		The rotor then internally uses this percentage to determines its spin speed.
	*/

	//The minimum rotation speed of the rotors
	const float minRotorPercent = 30.0f;

	//Shift the scale to be on positive scale
	float rotorSpeedOffset = (speed + maximumSpeed);
	
	//As scale has been offset, the max needs to be doubled 
	float maxSpeedOffset = maximumSpeed * 2;

	//get a percentage between 0%-70%
	float rotorSpeed = rotorSpeedOffset / maxSpeedOffset * 70;

	/*	Flip the percentage to the opposite and send it to the rotor
	This is done to make the animation run the correct way round
	It also adds the 30% minimum speed */
	rotor->setSpeedPercent((70 - rotorSpeed) + minRotorPercent);
}

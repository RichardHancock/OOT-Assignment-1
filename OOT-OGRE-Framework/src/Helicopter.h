#pragma once

#include "stdafx.h"

#include <memory>

#include "OgreApplication.h"

class Helicopter
{
public:

	Helicopter(Ogre::Vector3 pos);

	~Helicopter();

	Ogre::Vector3 getPos() { return pos; }

	void setPos(Ogre::Vector3 newPos);

	void setVelocity(Ogre::Vector3 newVel);

	void increaseVelocity(Ogre::Vector3 increase);

	/**
	@brief Sets the Helicopter's Rotor speed
	@param float - Speed of the main rotor
	@param float - Speed of the aft rotor
	*/
	void setRotorSpeed(float mainRotorSpeed, float aftRotorSpeed);

	void setActor(OgreApplication* app);

	void update(float dt);

	void updateRotors(float dt);

	std::string getNodeName() { return nodeName; }
private:

	std::shared_ptr<Ogre::SceneNode> heliNode;
	std::shared_ptr<Ogre::SceneNode> mainRotorNode;
	std::shared_ptr<Ogre::SceneNode> aftRotorNode;

	std::string nodeName;

	Ogre::Vector3 pos;

	Ogre::Vector3 vel;

	float mainRotorSpeed;
	float aftRotorSpeed;
};
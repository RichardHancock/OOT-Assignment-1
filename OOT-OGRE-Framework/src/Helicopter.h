#pragma once

#include "stdafx.h"

#include <memory>

#include "EntityWithMotion.h"
#include "OgreApplication.h"

class Helicopter : public EntityWithMotion
{
public:

	Helicopter(Ogre::Vector3 pos);

	virtual ~Helicopter();

	/**
	@brief Sets the Helicopter's Rotor speed
	@param float - Speed of the main rotor
	@param float - Speed of the aft rotor
	*/
	void setRotorSpeed(float mainRotorSpeed, float aftRotorSpeed);

	virtual void update(float dt);

	void updateRotors(float dt);

private:

	std::shared_ptr<Ogre::SceneNode> mainRotorNode;
	std::shared_ptr<Ogre::SceneNode> aftRotorNode;

	float mainRotorSpeed;
	float aftRotorSpeed;
};
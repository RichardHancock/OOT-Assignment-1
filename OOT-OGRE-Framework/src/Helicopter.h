#pragma once

#include "stdafx.h"

#include <memory>

#include "EntityWithMotion.h"
#include "OgreApplication.h"
#include "Rotor.h"

class Helicopter : public EntityWithMotion
{
public:

	Helicopter(Ogre::Vector3 pos, float maxSpeed);

	virtual ~Helicopter();

	virtual void setActor(OgreApplication* app, float angle, float scale, 
		std::string meshFile, std::string textureFile, Ogre::SceneNode* parent);

	virtual void update(float dt);

	void increaseRotatationSpeed(float speed);
	
	void handleInput(OIS::Keyboard* keyboard);
private:

	void calculateRotorSpeed(Rotor* rotor, float speed, float maximumSpeed);

	std::shared_ptr<Rotor> mainRotor;
	std::shared_ptr<Rotor> aftRotor;

	const float maxRotationSpeed;

	float rotationSpeed;
};
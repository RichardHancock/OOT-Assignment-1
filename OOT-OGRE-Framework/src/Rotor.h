#pragma once

#include "stdafx.h"

#include "Entity.h"

class Rotor : public Entity
{
public:

	Rotor(Ogre::Vector3 pos, float maxSpeed, Ogre::Vector3 rotationAxis);

	virtual ~Rotor();

	virtual void update(float dt);

	void setSpeedPercent(float percent);

	float getSpeedPercent() { return speed / maxSpeed * 100; }
	float getSpeedActual() { return speed; }

protected:
	
	float speed;

	float maxSpeed;

	unsigned int rotationAxis;
};
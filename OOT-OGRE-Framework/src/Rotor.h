#pragma once

#include "stdafx.h"

#include "Entity.h"

/**
@class Rotor
@brief A helicopter rotor that can spin at a passed in percentage
*/
class Rotor : public Entity
{
public:
	/**
	@brief Create Rotor
	@param Ogre::Vector3 - Starting Position
	@param float - Maximum rotation speed
	@param Ogre::Vector3 - Which axis should the rotor rotate around e.g (0,0,1) for z axis
	*/
	Rotor(Ogre::Vector3 pos, float maxSpeed, Ogre::Vector3 rotationAxis);

	virtual ~Rotor();

	/**
	@brief Update Internal values
	@param float - Delta time
	*/
	virtual void update(float dt);

	/**
	@brief Set the rotation speed percentage of the rotor. (0-100) Others will be ignored
	@param float - Speed Percentage
	*/
	void setSpeedPercent(float percent);

	/**
	@brief Get the current rotation speed percentage
	@return float - Speed Percentage
	*/
	float getSpeedPercent() { return speed / maxSpeed * 100; }

	/**
	@brief Get the current actual rotation speed
	@return float - Rotation speed
	*/
	float getSpeedActual() { return speed; }

protected:
	///Current rotation speed
	float speed;

	///Maximum rotation speed
	float maxSpeed;

	///Index position of which axis should be used when rotating (0=x,1=y,2=z)
	unsigned int rotationAxis;
};
#pragma once

#include "stdafx.h"

#include <memory>

#include "EntityWithMotion.h"
#include "OgreApplication.h"
#include "Rotor.h"

/**
@class Helicopter
@brief A player controlled helicopter with animated rotors
*/
class Helicopter : public EntityWithMotion
{
public:
	/**
	@brief Create Helicopter
	@param Ogre::Vector3 - Starting Position
	@param float - Maximum speed in all directions
	*/
	Helicopter(Ogre::Vector3 pos, float maxSpeed);

	virtual ~Helicopter();

	/**
	@brief Creates the scene node and loads mesh/texture. Also does the same for the rotors.
	@param OgreApplication* - The Apllication Pointer
	@param Ogre::Vector3 - Rotation in degrees
	@param float - Uniform scale
	@param std::string - Mesh filename/path
	@param std::string - Texture filename/path
	@param Ogre::SceneNode* - Supply the intended parent of this node, or nullptr for rootNode
	*/
	virtual void setActor(OgreApplication* app, Ogre::Vector3 angle, float scale, 
		std::string meshFile, std::string textureFile, Ogre::SceneNode* parent);
	
	/**
	@brief Update Internal values
	@param float - Delta time
	*/
	virtual void update(float dt);

	/**
	@brief Increases the Helicopter's current rotation by the passed in float
	@param float - Rotation increase amount in Radians
	*/
	void increaseRotatationSpeed(float speed);
	
	/**
	@brief Handles any Inputs related to the helicopter
	@param OIS::Keyboard* - Pointer to Keyboard
	*/
	void handleInput(OIS::Keyboard* keyboard);
private:
	/**
	@brief Calculates a rotor's speed based on a passed in range i.e 0-70

	0 is always the low end of the range
	@param Rotor* - A pointer to a rotor object
	@param float - Current position in range of numbers
	@param float - The maximum number in the range
	*/
	void calculateRotorSpeed(Rotor* rotor, float speed, float maximumSpeed);

	///The main rotor (top)
	std::shared_ptr<Rotor> mainRotor;

	///The Aft rotor
	std::shared_ptr<Rotor> aftRotor;

	///The maximum speed that the helicopter can rotate
	const float maxRotationSpeed;

	///The current rotation speed of the helicopter
	float rotationSpeed;
};
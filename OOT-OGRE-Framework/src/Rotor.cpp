#include "stdafx.h"
#include "Rotor.h"

#include "Util.h"

Rotor::Rotor(Ogre::Vector3 pos, float maxSpeed, Ogre::Vector3 rotationAxis)
	: Entity(pos), maxSpeed(maxSpeed)
{
	classType = "Rotor";

	speed = 0;

	//Stores which axis to rotate the rotor by
	if (rotationAxis.x != 0.00f)
		this->rotationAxis = 0;
	else if (rotationAxis.y != 0.00f)
		this->rotationAxis = 1;
	else if (rotationAxis.z != 0.00f)
		this->rotationAxis = 2;
	else
	{
		rotationAxis = 0;
		std::cout << "Error: No rotation axis given to rotor assuming X axis." << std::endl;
	}
}

Rotor::~Rotor()
{

}

void Rotor::update(float dt)
{
	float angle = speed * Ogre::Math::PI / 180.0f * dt;
	
	//Sets the angle to the relevant axis
	Ogre::Vector3 rotationVec(0.00f);
	rotationVec[rotationAxis] = angle;

	node->rotate(Ogre::Quaternion(Util::RotationMatrixXYZ(rotationVec)), Ogre::Node::TS_LOCAL);
}

void Rotor::setSpeedPercent(float percent)
{
	if (percent < 0.0f || percent > 100.0f)
	{
		std::cout << "Warning: Invalid Speed percentage passed to rotor, input was ignored" << std::endl;
		return;
	}
	
	//Set speed to the passed in percentage
	//Switch divide by 100 to multiply by 0.01, as multiply is faster for CPUs 
	speed = (maxSpeed / 100) * percent;
}
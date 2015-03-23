#pragma once

#include "stdafx.h"
#include "OgreMath.h"

namespace Util
{
	Ogre::Matrix3 RotationMatrixXYZ(Ogre::Vector3&  orientation);
	Ogre::Matrix3 rotate_x(float angle);
	Ogre::Matrix3 rotate_y(float angle);
	Ogre::Matrix3 rotate_z(float angle);

	float deg2Rad(float deg);
	
	void applyDrag(Ogre::Vector3& value, float dragAmount);

	void applyDrag(float& value, float dragAmount);
}
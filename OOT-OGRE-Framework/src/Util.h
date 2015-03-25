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

	void keepInBounds(Ogre::Vector3& value, float limit);

	void keepInBounds(float& value, float limit);

	class Timer
	{
	public:
		Timer();

		void reset();

		void reset(float newDuration);

		void update(float dt);

		bool hasTimerFinished() { return (current >= duration); }

	private:
		float current;

		float duration;
	};
}
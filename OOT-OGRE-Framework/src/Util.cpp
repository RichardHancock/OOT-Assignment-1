#include "stdafx.h"
#include "Util.h"

namespace Util
{
	//*** Exerise 3: define reusable utility functions
	Ogre::Matrix3 RotationMatrixXYZ(Ogre::Vector3&  orientation)
	{
		Ogre::Matrix3 rotateX, rotateY, rotateZ;
		const float angleX = orientation.x;
		const float angleY = orientation.y;
		const float angleZ = orientation.z;


		rotateX = Ogre::Matrix3(
			1.0, 0.0, 0.0,
			0.0, std::cos(angleX), -std::sin(angleX),
			0.0, std::sin(angleX), std::cos(angleX)
			);

		rotateY = Ogre::Matrix3(
			std::cos(angleY), 0.0, std::sin(angleY),
			0.0, 1.0, 0.0,
			-std::sin(angleY), 0.0, std::cos(angleY)
			);

		rotateZ = Ogre::Matrix3(
			std::cos(angleZ), -std::sin(angleZ), 0.0,
			std::sin(angleZ),  std::cos(angleZ), 0.0,
			0.0, 0.0, 1.0
			);

		Ogre::Matrix3 rotation = rotateZ*rotateY*rotateX;

		return rotation;
	}

	Ogre::Matrix3 rotate_x(float angle)
	{
		Ogre::Matrix3 matX, rotateY, rotateZ;
		matX = Ogre::Matrix3(
			1.0, 0.0, 0.0,
			0.0, std::cos(angle), -std::sin(angle),
			0.0, std::sin(angle), std::cos(angle)
			);

		return matX;
	}

	Ogre::Matrix3 rotate_y(float angle)
	{
		Ogre::Matrix3 matY;
		matY = Ogre::Matrix3(
			std::cos(angle), 0.0, std::sin(angle),
			0.0, 1.0, 0.0,
			-std::sin(angle), 0.0, std::cos(angle)
			);
		return matY;
	}

	Ogre::Matrix3 rotate_z(float angle)
	{
		Ogre::Matrix3 matZ;

		matZ = Ogre::Matrix3(
			std::cos(angle), -std::sin(angle), 0.0,
			std::sin(angle), std::cos(angle), 0.0,
			0.0, 0.0, 1.0
			);
		return matZ;
	}

	void deg2Rad(Ogre::Vector3& deg)
	{
		deg.x = deg2Rad(deg.x);
		deg.y = deg2Rad(deg.y);
		deg.z = deg2Rad(deg.z);
	}

	float deg2Rad(float deg)
	{
		return deg * 0.0174532925f;
	}

	void applyDrag(Ogre::Vector3& value, float dragAmount)
	{
		applyDrag(value.x, dragAmount);
		applyDrag(value.y, dragAmount);
		applyDrag(value.z, dragAmount);
	}

	void applyDrag(float& value, float dragAmount)
	{

		if (value == 0.00f)
		{
			//Value already 0 no drag can be applied
			return;
		}

		if (value < 0.00f)
		{
			//Something HERE WRONG
			if (value < -dragAmount)
			{
				value += dragAmount;
			}
			else
			{
				value = 0;
			}
		}
		else
		{
			if (value > dragAmount)
			{
				value -= dragAmount;
			}
			else
			{
				value = 0;
			}
		}

	}

	void keepInBounds(Ogre::Vector3& value, float limit)
	{
		keepInBounds(value.x, limit);
		keepInBounds(value.y, limit);
		keepInBounds(value.z, limit);
	}

	void keepInBounds(float& value, float limit)
	{
		if (value < -limit)
		{
			value = -limit;
		}
		else if (value > limit)
		{
			value = limit;
		}
	}


	//Timer
	Timer::Timer()
	{
		duration = 10.0f;
		
		//Set the current to be past the duration so the timer is stopped
		current = 11.0f;
	}

	float Timer::getTimeRemaining()
	{
		if (hasTimerFinished())
		{
			//Stops negative numbers being returned
			return 0.00f;
		}
		else
		{
			return duration - current;
		}
	}

	void Timer::reset()
	{
		current = 0.0f;
	}

	void Timer::reset(float newDuration)
	{
		current = 0.0f;
		duration = newDuration;
	}

	void Timer::update(float dt)
	{
		if (!hasTimerFinished())
		{
			current += dt;
		}
	}


}
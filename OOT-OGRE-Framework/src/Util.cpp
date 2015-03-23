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
			if (value < -dragAmount)
			{
				value += dragAmount;
			}
			else
			{
				value += value;
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
				value -= value;
			}
		}

	}
}
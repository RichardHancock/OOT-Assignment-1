#pragma once

#include "stdafx.h"
#include "OgreMath.h"

///Contains many useful Utility functions
namespace Util
{
	/**
	@brief Converts a Vec3 rotation into a rotation matrix
	@param Ogre::Vector3& - Vector containing all 3 rotations
	@return Ogre::Matrix3 - XYZ Rotation Matrix
	*/
	Ogre::Matrix3 RotationMatrixXYZ(Ogre::Vector3&  orientation);
	
	/**
	@brief Converts an X rotation into a rotation matrix
	@param float - X axis rotation angle
	@return Ogre::Matrix3 - X Rotation Matrix
	*/
	Ogre::Matrix3 rotate_x(float angle);
	
	/**
	@brief Converts an Y rotation into a rotation matrix
	@param float - Y axis rotation angle
	@return Ogre::Matrix3 - Y Rotation Matrix
	*/
	Ogre::Matrix3 rotate_y(float angle);
	
	/**
	@brief Converts an Z rotation into a rotation matrix
	@param float - Z axis rotation angle
	@return Ogre::Matrix3 - Z Rotation Matrix
	*/
	Ogre::Matrix3 rotate_z(float angle);

	/**
	@brief Converts all dimensions of a Vec3 from degrees to radians
	@param Ogre::Vector3& - Vector3 to modify
	*/
	void deg2Rad(Ogre::Vector3& deg);

	/**
	@brief Converts a value from degrees to radians and returns the result
	@param float - Value in degrees
	@return float - Converted value in radians
	*/
	float deg2Rad(float deg);
	
	/**
	@brief Applies a drag amount to all elements of a Vector
	@param Ogre::Vector3& - Vector to modify
	@param float - Amount of drag to apply
	*/
	void applyDrag(Ogre::Vector3& value, float dragAmount);

	/**
	@brief Decreases a float by a certain amount (works with negatives as well)
	@param float& - float to modify
	@param float - Amount of drag to apply
	*/
	void applyDrag(float& value, float dragAmount);

	/**
	@brief Keeps a vector3's values within a certain limit
	Between -limit to limit

	@param Ogre::Vector3& - Vector to modify
	@param float - Value limit
	*/
	void keepInBounds(Ogre::Vector3& value, float limit);

	/**
	@brief Keeps a float within a certain limit, Between -limit to limit
	@param float& - float to modify
	@param float - Value limit
	*/
	void keepInBounds(float& value, float limit);

	/**
	@class Timer
	@brief A simple countdown timer that runs using Pseudo Seconds (tied to DT)
	*/
	class Timer
	{
	public:
		///Create the Timer
		Timer();

		/**
		@brief Get the time remaining in seconds
		@return float - Time in seconds
		*/
		float getTimeRemaining();

		///Restart the timer using the previous duration, or if no previous its 10s
		void reset();

		/**
		@brief Restart the timer and set its duration to the passed in value
		@param float - New timer duration in seconds 
		*/
		void reset(float newDuration);

		///Stops the currently running timer 
		void stop();

		/**
		@brief Increments the timer (Required for operation)
		@param float - Delta time 
		*/
		void update(float dt);

		/**
		@brief Has the timer finished
		@return bool - True if finished, else false
		*/
		bool hasTimerFinished() { return (current >= duration); }

	private:
		///Current Time
		float current;

		///The Current duration
		float duration;
	};
}
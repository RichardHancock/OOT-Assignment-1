#pragma once

#include "stdafx.h"

#include <memory>

#include "OgreApplication.h"

/**
@class Entity
@brief An object appears in the game world
*/
class Entity
{
public:
	Entity(Ogre::Vector3 pos);

	virtual ~Entity();

	Ogre::Vector3 getPos() { return pos; }

	void setPos(Ogre::Vector3 newPos);

	void setActor(OgreApplication* app, float angle, float scale,
		std::string meshFile, std::string textureFile);

	virtual void update(float dt);

	std::string getNodeName() { return nodeName; }

protected:

	static std::string classType;

	///Entity's Scene Node
	std::shared_ptr<Ogre::SceneNode> node;

	///Name of the Scene Node
	std::string nodeName;

	///Position of the entity
	Ogre::Vector3 pos;


	static unsigned int entityID;

	static void generateNextID();
};
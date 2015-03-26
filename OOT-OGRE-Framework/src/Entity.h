#pragma once

#include "stdafx.h"

#include <memory>

#include "OgreApplication.h"

/**
@class Entity
@brief An object that appears in the game world
*/
class Entity
{
public:
	/**
	@brief Create Entity
	@param Ogre::Vector3 - Starting Position
	*/
	Entity(Ogre::Vector3 pos);

	virtual ~Entity();

	/**
	@brief Returns the Entity's current position
	@return Ogre::Vector3 - Position
	*/
	Ogre::Vector3 getPos() { return pos; }

	/**
	@brief Sets the Entity's current position
	@param Ogre::Vector3 - Position
	*/
	void setPos(Ogre::Vector3 newPos);

	/**
	@brief Creates the scene node and loads mesh/texture 
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
	@brief Returns the Entity's scene node's name
	@return std::string - Node Name
	*/
	std::string getNodeName() { return nodeName; }

protected:
	///Name of the class for use as its scene node name
	std::string classType;

	///Entity's Scene Node
	std::shared_ptr<Ogre::SceneNode> node;

	///Name of the Scene Node
	std::string nodeName;

	///Position of the entity
	Ogre::Vector3 pos;

	///This stores the next available entityID
	static unsigned int entityID;

	///Increments the entityID once a ID has been used
	static void generateNextID();

private:
	/**
	@brief Load a texture and return its assigned name
	@param std::string - Texture filename/path
	@return std::string - Material's name (Used in setMaterialName)
	*/
	std::string loadTexture(std::string filename);
};

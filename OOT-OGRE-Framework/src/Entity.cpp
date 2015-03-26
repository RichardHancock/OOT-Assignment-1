#include "stdafx.h"
#include "Entity.h"

#include <math.h>

#include "Util.h"

unsigned int Entity::entityID = 0;

Entity::Entity(Ogre::Vector3 pos)
	: pos(pos)
{
	classType = "Entity";
}

Entity::~Entity() 
{
	node.reset();
}

void Entity::setPos(Ogre::Vector3 newPos)
{
	pos = newPos;
}

void Entity::setActor(OgreApplication* app, Ogre::Vector3 angle, float scale,
					  std::string meshFile, std::string textureFile, Ogre::SceneNode* parent)
{
	//Create node name from class name and Unique ID
	nodeName = classType + to_string(entityID);

	//Now this ID has been used, generate a new one
	generateNextID();

	//Convert to radians
	Util::deg2Rad(angle);

	Ogre::Matrix3 rotation(Util::RotationMatrixXYZ(angle));

	Ogre::Quaternion orientationQ(rotation);

	auto mesh = app->GetSceneManager()->createEntity(meshFile);
	mesh->setCastShadows(false);

	//Load the texture and apply it to the mesh
	mesh->setMaterialName(loadTexture(textureFile));

	Ogre::SceneNode* tempNode;

	if (parent == nullptr)
	{
		tempNode = app->GetSceneManager()->getRootSceneNode()
			->createChildSceneNode(nodeName);
	}
	else
	{
		tempNode = parent->createChildSceneNode(nodeName);
	}
	

	tempNode->setScale(Ogre::Vector3(scale));
	tempNode->setPosition(pos);
	tempNode->setOrientation(orientationQ);
	tempNode->attachObject(mesh);
	tempNode->showBoundingBox(false);

	node.reset(tempNode);

}

std::string Entity::loadTexture(std::string filename)
{
	//Cuts the file extension off and uses the rest for the material name
	size_t dotPosition = filename.find('.', 0);
	std::string materialName = filename.substr(0, dotPosition);

	//Creates a material using the texture file name minus 4 characters (.png)
	Ogre::MaterialPtr material =
		Ogre::MaterialManager::getSingleton().create(
		materialName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	Ogre::Technique* firstTechnique = material->getTechnique(0);
	Ogre::Pass* firstPass = firstTechnique->getPass(0);

	Ogre::TextureUnitState* textureUnit = firstPass->createTextureUnitState();
	textureUnit->setTextureName(filename, Ogre::TEX_TYPE_2D);
	textureUnit->setTextureCoordSet(0);

	return materialName;
}


void Entity::update(float dt)
{
	if (node != nullptr)
	{
		node->setPosition(pos);
	}
}

void Entity::generateNextID()
{
	entityID++;
}
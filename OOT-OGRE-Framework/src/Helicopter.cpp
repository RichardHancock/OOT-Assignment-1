#include "stdafx.h"
#include "Helicopter.h"

#include <math.h>

#include "Util.h"

Helicopter::Helicopter(Ogre::Vector3 pos) 
{
	vel = 0;
	this->pos = pos;
}

Helicopter::~Helicopter() { }

void Helicopter::setPos(Ogre::Vector3 newPos)
{
	pos = newPos;
}

void Helicopter::setVelocity(Ogre::Vector3 newVel)
{
	vel = newVel;
}

void Helicopter::increaseVelocity(Ogre::Vector3 increase)
{
	vel += increase;
}

void Helicopter::setRotorSpeed(float mainRotorSpeed, float aftRotorSpeed)
{
	this->mainRotorSpeed = mainRotorSpeed;
	this->aftRotorSpeed = aftRotorSpeed;
}

void Helicopter::setActor(OgreApplication* app)
{

	float angle = 90.0f * Ogre::Math::PI / 180.0f;
	Ogre::Matrix3 rotateX(Util::RotationMatrixXYZ(Ogre::Vector3(angle, 0, 0)));

	Ogre::Quaternion orientationQ(rotateX);

	Ogre::Real scale = 200.0f;

	auto helicopter = app->GetSceneManager()->createEntity("helicopter.mesh");
	helicopter->setCastShadows(false);

	Ogre::MaterialPtr material =
		Ogre::MaterialManager::getSingleton().create(
		"GREEN", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	Ogre::Technique* firstTechnique = material->getTechnique(0);
	Ogre::Pass* firstPass = firstTechnique->getPass(0);

	Ogre::TextureUnitState* textureUnit = firstPass->createTextureUnitState();
	textureUnit->setTextureName("green.png", Ogre::TEX_TYPE_2D);
	textureUnit->setTextureCoordSet(0);

	helicopter->setMaterialName("GREEN");
	auto node1 = app->GetSceneManager()->getRootSceneNode()
		->createChildSceneNode("helicopter");
	nodeName = "helicopter";

	node1->setScale(Ogre::Vector3(scale));
	node1->setPosition(pos);
	node1->setOrientation(orientationQ);
	node1->attachObject(helicopter);
	node1->showBoundingBox(false);

	heliNode.reset(node1);

	//Rotors
	auto mainRotor = app->GetSceneManager()->createEntity("topRotor.mesh");
	mainRotor->setCastShadows(false);

	Ogre::Vector3 mainRotorPos(0.0f, 0.0f, -0.045f);

	mainRotor->setMaterialName("GREEN");

	auto node2 = heliNode->createChildSceneNode("mainRotor");
	node2->setPosition(mainRotorPos);
	node2->attachObject(mainRotor);
	node2->showBoundingBox(false);
	mainRotorNode.reset(node2);

	auto aftRotor = app->GetSceneManager()->createEntity("aftRotor.mesh");
	aftRotor->setCastShadows(false);

	Ogre::Vector3 aftRotorPos(-0.015f, -0.11f, -0.004f);

	aftRotor->setMaterialName("GREEN");

	auto node3 = heliNode->createChildSceneNode("aftRotor");
	node3->setPosition(aftRotorPos);
	node3->attachObject(aftRotor);
	node3->showBoundingBox(false);
	aftRotorNode.reset(node3);
}

void Helicopter::update(float dt)
{
	Util::applyDrag(vel, 0.40f);
	pos += vel * dt;
	heliNode->setPosition(pos);

	updateRotors(dt);
}

void Helicopter::updateRotors(float dt)
{
	float angle = mainRotorSpeed * Ogre::Math::PI / 180.0f * dt;
	mainRotorNode->rotate(Ogre::Quaternion(Util::RotationMatrixXYZ(Ogre::Vector3(0, 0, angle))), Ogre::Node::TS_LOCAL);
	
	angle = aftRotorSpeed * Ogre::Math::PI / 180.0f * dt;
	aftRotorNode->rotate(Ogre::Quaternion(Util::RotationMatrixXYZ(Ogre::Vector3(angle, 0, 0))), Ogre::Node::TS_LOCAL);
}
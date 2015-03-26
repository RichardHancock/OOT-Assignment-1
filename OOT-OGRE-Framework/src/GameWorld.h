
#pragma once
#ifndef _GAME_WORLD_H_
#define _GAME_WORLD_H_

#include "stdafx.h"
#include <iostream>
#include "OgreApplication.h"

#include "Helicopter.h"
#include "Cannon.h"
#include "Camera.h"
#include "TerrainManager.h"

/**
@class GameWorld
@brief Contains the Renderable world and game objects 
*/
class GameWorld : public OgreBites::SdkTrayListener
{
private:
	
	/**
	@brief Updates the Game objects internal values
	@param float - Delta time
	*/
	void UpdateGame(float dt);
	
	///Create the GUI elements
	void CreateGUI();

	///Initializes the scene (Calls the create functions)
	void InitilaiseScene();

	///Loads the map using the terrain manager
	void CreateEnviroment();

	///Creates the Game objects and loads up their meshes
	void CreateEntities();

	/**
	@brief Calls the updateGame function and updates the GUI
	@param float - Delta time
	*/
	void Update(float dt);

	/**
	@brief Handles any inputs
	@param OIS::Mouse* - Mouse Pointer
	@param OIS::Keyboard* - Keyboard Pointer
	@param Ogre::SceneNode* - Pointer to the main camera node
	@param Camera* - Pointer to the main camera object
	@return bool - Should the game exit
	*/
	bool handleInputs(OIS::Mouse* mouse, OIS::Keyboard* keyboard, Ogre::SceneNode* cameraNode, Camera* camera);

	//Game Objects
	///Player Helicopter pointer
	shared_ptr<Helicopter> heli;
	
	///Cannon Pointer
	std::vector<shared_ptr<Cannon>> cannons;

	///Vector of all fired bullets
	std::vector<shared_ptr<Projectile>> bullets;


	//GUI
	shared_ptr<OgreBites::SdkTrayManager> trayManager;
	Ogre::FrameEvent frameEvent;
	OgreBites::InputContext inputContext;
	OgreBites::ParamsPanel* paramPanel;

	///Terrain Manager
	shared_ptr<TerrainManager> terrainManager;

	///Application pointer
	OgreApplication* application;
	
public:
	/**
	@brief Create the GameWorld
	@param OgreApplication* - Application Pointer
	*/
	GameWorld(OgreApplication* application_);

	~GameWorld();
	
	///Main Game Loop
	void Run();


	
};

#endif // End of _GAME_WORLD_H_

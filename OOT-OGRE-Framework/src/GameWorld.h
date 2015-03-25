//
//  GameWorld.h
// This class is the interface class between your game to Ogre.
// The access point is the pointer to OgreApplication class 
//  OOT Tutorial Ogre Framework Demo.
//  Created by Wen Tang on 19/01/15.
//

#pragma once
#ifndef _GAME_WORLD_H_
#define _GAME_WORLD_H_

#include "stdafx.h"
#include <iostream>
#include "OgreApplication.h"

#include "Helicopter.h"
#include "Cannon.h"

#include "TerrainManager.h"

class GameWorld : public OgreBites::SdkTrayListener
{
private:
										
	void UpdateGame(float dt);
	void UpdateScene(Ogre::Vector3 &pos, Ogre::Quaternion &q);
	
	void CreateGUI();

	shared_ptr<Helicopter> heli;
	shared_ptr<Cannon> cannon;
	std::vector<shared_ptr<Projectile>> bullets;


	//GUI
	shared_ptr<OgreBites::SdkTrayManager> trayManager;
	Ogre::FrameEvent frameEvent;
	OgreBites::InputContext inputContext;
	OgreBites::ParamsPanel* paramPanel;

	shared_ptr<TerrainManager> terrainManager;

	OgreApplication* application;
	
public:

	GameWorld(OgreApplication* application_);
	~GameWorld();
					
	void Run();
	void InitilaiseScene();
	void CreateEnviroment();
	void CreateLights();
	void CreateEntities();
	void Update(float dt);
	
	void Reset();

};

#endif // End of _GAME_WORLD_H_

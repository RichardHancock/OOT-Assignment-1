//
//  GameWorld.cpp
//  OOT Tutorial Ogre Framework Demo.
//  Created by Wen Tang on 19/01/15.
//
#include "stdafx.h"
#include "GameWorld.h"
#include "Camera.h"

#include <string>
#include <iostream>
#include <sstream>

#include "Util.h"

#define STEP_LENGTH 0.03

GameWorld::GameWorld(OgreApplication* application_) 
{
	application = application_;
	trayManager = nullptr;
	terrainManager = nullptr;
	frameEvent = Ogre::FrameEvent();
}


GameWorld::~GameWorld()
{
}

void GameWorld::InitilaiseScene()
{
	CreateEnviroment();
	CreateEntities();
	CreateGUI();
}

void GameWorld::CreateGUI()
{
	OgreBites::InputContext inputContext;
	inputContext.mKeyboard = application->GetKeyboard().get();
	inputContext.mMouse = application->GetMouse().get();
	trayManager = make_shared<OgreBites::SdkTrayManager>("GUI", application->GetRenderWindow()
		,inputContext, this);

	trayManager->showFrameStats(OgreBites::TL_BOTTOMRIGHT);
	trayManager->showLogo(OgreBites::TL_BOTTOMRIGHT);
	trayManager->hideCursor();

	Ogre::StringVector parameters;
	parameters.push_back("Helicopter Position");
	parameters.push_back("Current Reload Time");
	paramPanel = trayManager->createParamsPanel(OgreBites::TL_TOPLEFT,"Parameter Panel", 350, parameters);
}

void GameWorld::CreateEntities()
{
	
	// Create a material object named "RED" and a material object "GREEN"
	application->SetEntityColour("RED", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::ColourValue(1.0f, 0.1f, 0.1f), Ogre::ColourValue(0.6f, 0.0f, 0.0f), 100.0f);
	application->SetEntityColour("GREEN", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::ColourValue(0.1f, 0.8f, 0.1f), Ogre::ColourValue(0.0f, 0.6f, 0.0f), 50.0f);

	heli.reset(new Helicopter(Ogre::Vector3(0,300,0), 100.0f));
	heli->setActor(application, Ogre::Vector3(90.0f, 0.0f, 0.0f), 200.0f, "helicopter.mesh", "green.png", nullptr);

	Ogre::Vector3 cannonPositions[2] = {
		Ogre::Vector3(100,265,227),
		Ogre::Vector3(-112,265,295)
	};

	cannons.resize(2);

	for (unsigned int i = 0; i < cannons.size(); i++)
	{
		cannons[i].reset(new Cannon(cannonPositions[i]));
		cannons[i]->setActor(application, Ogre::Vector3(0.0f), 0.2f, "cube.mesh", "MtlPlat2.jpg", nullptr);
	}
}

// Create a ogre world environment with a predefined geometry and a texture
void GameWorld::CreateEnviroment()
{
	terrainManager = make_shared<TerrainManager>();
	terrainManager->Create(application->GetSceneManager());
	terrainManager->Loaded();

	Ogre::Plane plane;
	plane.d = 100;
	plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
	
	application->GetSceneManager()->setSkyDome(true, "Examples/CloudySky", 10, 8, 100);
	
}

void GameWorld::Run()
{
	
	//Create the game world
     InitilaiseScene();
	
	 // Create a camera
	 Ogre::String cameraName = "MainCamera";
	 auto cameraNode = application->CreateCamera(cameraName, 
		 application->GetSceneManager()->getSceneNode(heli->getNodeName()));

	 //Move it behind the helicopter
	 cameraNode->translate(0.0f, 0.0f, -80.0f, Ogre::Node::TS_WORLD);
	 //Look at the helicopter
	 static_cast<Ogre::Camera*>(cameraNode->getAttachedObject("MainCamera"))->lookAt(heli->getPos());
	 shared_ptr<Ogre::MovableObject> cameraObject;
	 cameraObject.reset(cameraNode->getAttachedObject("MainCamera"));
	 
	 std::shared_ptr<Camera> camera = make_shared<Camera>(cameraNode, cameraObject);

	//Create input device listeners 
	application->CreateIOS();
	auto keyboard = application->GetKeyboard();
	auto mouse = application->GetMouse();

	// Create Timer
	auto timer = application->CreateTimer();
	timer->reset();
    unsigned long lastTime = timer->getMilliseconds();
	unsigned long deltaTime = 0;
	float deltaTime_s = 0.0f;
    application->GetOgreWrapper().GetRoot()->clearEventTimes();
    double timeToUpdate = 0.0;
    unsigned int index = 0;
    float elapsedTime = 0.0f;


	//Game loop
	while (!application->GetOgreWrapper().GetWindow()->isClosed())
	{

		//Evaluate the current time and the time elapsed since last frame 
		//Prepare the next iteration. 	
		unsigned long currentTime = timer->getMilliseconds();
		deltaTime = currentTime - lastTime;
		if(deltaTime == 0)  continue;

		lastTime = currentTime;
		deltaTime_s = 0.001f * float(deltaTime);

		//Input Handling
		if (handleInputs(mouse.get(), keyboard.get(), cameraNode.get(), camera.get()))
			break;

		frameEvent.timeSinceLastFrame = deltaTime;
		trayManager->frameRenderingQueued(frameEvent);

		elapsedTime += deltaTime;
		if (elapsedTime > 100)
		{
			// do something
			elapsedTime = 0;
		}

		timeToUpdate += deltaTime_s;
		unsigned int numOfUpdates = 0;

		while (timeToUpdate > STEP_LENGTH && numOfUpdates < 60)
		{
			timeToUpdate -= STEP_LENGTH;
			
			Update(deltaTime_s);

			static_cast<Ogre::Camera*>(cameraNode->getAttachedObject("MainCamera"))->lookAt(heli->getPos());
	
			numOfUpdates++;
		}
		
		// Update window false
		bool updateWin = false;
		bool verticalSynchro = true;
		application->Run(updateWin, verticalSynchro);

		Ogre::WindowEventUtilities::messagePump();
	}

	application->CleanUp();
 
}

void GameWorld::UpdateGame(float dt)
{
	// Implement ...... 
	heli->update(dt);
	
	//Update and aim cannons
	for (auto cannon : cannons)
	{
		cannon->update(dt);
		cannon->aim(heli->getPos());
	}
	
	for (unsigned int i = 0; i < bullets.size();)
	{
		auto bullet = bullets[i];

		bullet->update(dt);

		if (bullet->expired())
		{
			bullets.erase(bullets.begin() + i);
		}
		else
		{
			i++;
		}
	}
		
}

void GameWorld::Update(float dt)
{
	UpdateGame(dt);

	//Heli Position
	char buffer[256];
	Ogre::SceneNode *helicopterNode = application->GetSceneManager()->getSceneNode(heli->getNodeName());
	Ogre::Vector3 vValue = helicopterNode->getPosition();
	sprintf_s(buffer, 256, "%4.2f %4.2f %4.2f", vValue.x, vValue.y, vValue.z);
	paramPanel->setParamValue(0, buffer);

	//Reload Time (Only gets it from one as they should be near identical)
	sprintf_s(buffer, 256, "%4.2f seconds", cannons[0]->getRemainingReloadTime());
	paramPanel->setParamValue(1, buffer);

}

bool GameWorld::handleInputs(OIS::Mouse* mouse, OIS::Keyboard* keyboard, Ogre::SceneNode* cameraNode, Camera* camera)
{
	keyboard->capture();
	mouse->capture();
	camera->Update(keyboard, mouse);
	
	heli->handleInput(keyboard);

	//Quit Game
	if (keyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		return true;
	}

	//Debug Views
	else if (keyboard->isKeyDown(OIS::KC_V)){
		auto camera = static_cast<Ogre::Camera*>(cameraNode->getAttachedObject("MainCamera"));
		camera->setPolygonMode(Ogre::PM_WIREFRAME);
	}
	else if (keyboard->isKeyDown(OIS::KC_B))
	{
		auto camera = static_cast<Ogre::Camera*>(cameraNode->getAttachedObject("MainCamera"));
		camera->setPolygonMode(Ogre::PM_POINTS);
	}
	else if (keyboard->isKeyDown(OIS::KC_N))
	{
		auto camera = static_cast<Ogre::Camera*>(cameraNode->getAttachedObject("MainCamera"));
		camera->setPolygonMode(Ogre::PM_SOLID);
	}

	//Fire Cannon
	if (keyboard->isKeyDown(OIS::KC_SPACE))
	{
		for (auto cannon : cannons)
		{
			//Fire a bullet and push it into the array of bullets
			shared_ptr<Projectile> newBullet = cannon->fire();

			if (newBullet != nullptr)
			{
				newBullet->setActor(application, Ogre::Vector3(0.0f), 0.03f, "sphere.mesh", "floor_diffuse.PNG", nullptr);
				bullets.push_back(newBullet);
			}
		}
	}

	return false;
}
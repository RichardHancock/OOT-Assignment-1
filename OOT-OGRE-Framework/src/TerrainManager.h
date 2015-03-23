//
//  TerrainManager.h
//  OOT Tutorial Ogre Framework Demo.
//  This class is based on Ogre Basic Tutorial 3
//  http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Basic+Tutorial+3&structure=Tutorials
//  Created by Wen Tang on 10/02/15.
//

#ifndef _TERRAIN_MANAGER_H_
#define _TERRAIN_MANAGER_H_

#include "stdafx.h"
#include <iostream>
#include "OgreApplication.h"

#include "Terrain/OgreTerrain.h"
#include "Terrain/OgreTerrainGroup.h"

class TerrainManager
{
private:
							      
	shared_ptr<Ogre::TerrainGlobalOptions> terrainGlobals;
    Ogre::TerrainGroup* terrainGroup;
    bool terrainImported;
 
public:
	TerrainManager();
	~TerrainManager();

	void Create( Ogre::SceneManager* sMgr);
	void Loaded();

private:
	
    void DefineTerrain(long x, long y);
    void InitBlendMaps(Ogre::Terrain* terrain);
    void ConfigureTerrainDefaults(Ogre::Light* light, const Ogre::ColourValue& ambientLight);
	void GetTerrainHightMap(bool flipX, bool flipY, Ogre::Image& hMap);

};

#endif
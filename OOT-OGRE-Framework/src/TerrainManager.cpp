//
//  TerrainManager.cpp
//  OOT Tutorial Ogre Framework Demo.
//  This class is based on Ogre Basic Tutorial 3
//  http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Basic+Tutorial+3&structure=Tutorials
//  Created by Wen Tang on 10/02/15.
//

#include "stdafx.h"
#include "TerrainManager.h"


TerrainManager::TerrainManager()
{
	terrainImported = false;
}


TerrainManager::~TerrainManager()
{
}

//\brief Create terrain
void TerrainManager::Create( Ogre::SceneManager* sMgr)
{
	auto sceneMgr = sMgr;
	
	// set a light to lit the terrain
	Ogre::Vector3 lightdir(0.55f, -0.3f, 0.75f);
    lightdir.normalise();

    auto light = sceneMgr->createLight("terrainLight");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(lightdir);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue(0.4f, 0.4f, 0.4f));

	sceneMgr->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f,0.2f));
	
	terrainGlobals = make_shared<Ogre::TerrainGlobalOptions>();
	terrainGroup = new Ogre::TerrainGroup(sceneMgr, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);
	terrainGroup->setFilenameConvention(Ogre::String("BasicTutorial3Terrain"), Ogre::String("dat"));
	terrainGroup->setOrigin(Ogre::Vector3::ZERO);
	
	const Ogre::ColourValue ambientLight =  sceneMgr->getAmbientLight();
	ConfigureTerrainDefaults(light, ambientLight);

	for (long x = 0; x <= 0; ++x)    // only one terrain for now
		for(long y = 0; y <= 0; ++y) // only one terrain for now
			DefineTerrain(x, y);     // x = 0, y = 0
	
	// sync load since we want everything in place when we start
    terrainGroup->loadAllTerrains(true);

	if(terrainImported)
	{
		Ogre::TerrainGroup::TerrainIterator ti = terrainGroup->getTerrainIterator();

		while(ti.hasMoreElements())
		{
			Ogre::Terrain* t = ti.getNext()->instance;
			InitBlendMaps(t);
		}
	}
	
	terrainGroup->saveAllTerrains(true);
	terrainGroup->freeTemporaryResources();
 
    Ogre::ColourValue fadeColour(0.9f, 0.9f, 0.9f);
    sceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0.f, 300.f, 600.f);
   
}

void TerrainManager::ConfigureTerrainDefaults(Ogre::Light* light, const Ogre::ColourValue& ambientLight)
{
	
	// Important to set these so that the terrain knows what to use for derived (non-realtime) data 
	// Configure global
    terrainGlobals->setMaxPixelError(8);
	terrainGlobals->setCompositeMapDistance(3000);
	terrainGlobals->setLightMapDirection(light->getDerivedDirection());
	terrainGlobals->setCompositeMapAmbient(ambientLight);
	terrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

	// Configure default import settings for imported images if any
	Ogre::Terrain::ImportData& defaultimp = terrainGroup->getDefaultImportSettings();
	defaultimp.terrainSize = 513;
	defaultimp.worldSize = 12000.0f;
	defaultimp.inputScale = 600;
	defaultimp.minBatchSize = 33;
	defaultimp.maxBatchSize = 65;
	// Textures
	defaultimp.layerList.resize(3);
	defaultimp.layerList[0].worldSize = 100;
	defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
	defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
	defaultimp.layerList[1].worldSize = 30;
	defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
	defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
	defaultimp.layerList[2].worldSize = 200;
	defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
	defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");

}

void TerrainManager::DefineTerrain(long x, long y)
{
	Ogre::String filename = terrainGroup->generateFilename(x, y);
	if(Ogre::ResourceGroupManager::getSingleton().resourceExists(terrainGroup->getResourceGroup(), filename))
	{
		terrainGroup->defineTerrain(x, y);
	}
	else
	{
		Ogre::Image hight_map;
		GetTerrainHightMap(x %2 !=0, y%2 !=0, hight_map);
		terrainGroup->defineTerrain(x, y, &hight_map);
		terrainImported = true;
	}

}

void TerrainManager::GetTerrainHightMap(bool flipX, bool flipY, Ogre::Image& hMap)
{

	hMap.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	if(flipX) hMap.flipAroundY();
	if(flipY) hMap.flipAroundX();

}

void TerrainManager::InitBlendMaps(Ogre::Terrain* terrain)
{
	Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
	Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
	Ogre::Real minHeight0 = 70;
	Ogre::Real fadeDist0 = 40;
	Ogre::Real minHeight1 = 70;
	Ogre::Real fadeDist1 = 15;
	auto pBlend1 = blendMap1->getBlendPointer();
	for(Ogre::uint16 y = 0 ; y<terrain->getLayerBlendMapSize(); ++y)
	{
		for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
        {

			Ogre::Real tx, ty;

			blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
			Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
			Ogre::Real val = (height - minHeight0)/fadeDist0;
			val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);

			val = (height - minHeight1) / fadeDist1;
			val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
			*pBlend1++ = val;
		}
	}
	blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();

}

void TerrainManager::Loaded()
{

	if (terrainGroup->isDerivedDataUpdateInProgress())
    {
        if (terrainImported)
        {
            printf("Building terrain, please wait...");
        }
		else
        {
            printf("Updating textures, patience...");
        }
    } 
	else if (terrainImported)
    {
      
            terrainGroup->saveAllTerrains(true);
            terrainImported = false;
		    printf("Terrain loaded !!!");
    }
 
}
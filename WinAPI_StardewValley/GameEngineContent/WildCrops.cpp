#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "WildCrops.h"

WildCrops::WildCrops()
{

}

WildCrops::~WildCrops()
{

}

void WildCrops::Start()
{
	ContentCrops::Start();
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 3);
	std::string FileName = "";
	switch (RandomValue)
	{
	case 0:
		CropsName = "Daffodil.bmp";
		break;
	case 1:
		CropsName = "Dandelion.bmp";
		break;
	case 2:
		CropsName = "Wasabi.bmp";
		break;
	case 3:
		CropsName = "Leeks.bmp";
		break;
	default:
		break;
	}
	if (false == ResourcesManager::GetInst().IsLoadTexture("Crops_" + CropsName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Crops\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Crops_" + CropsName));
		ResourcesManager::GetInst().CreateSpriteSheet("Crops_" + CropsName, 4, 1);
	}
	CropsRenderer->SetSprite("Crops_" + CropsName, GrowStep);
	MaxGrowStep = 3;
}
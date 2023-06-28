#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Rhubarb.h"

Rhubarb::Rhubarb()
{

}

Rhubarb::~Rhubarb()
{

}

void Rhubarb::Start()
{
	ContentCrops::Start();
	CropsName = "Rhubarb.bmp";
	if (false == ResourcesManager::GetInst().IsLoadTexture("Crops_Rhubarb.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Crops\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Crops_Rhubarb.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Crops_Rhubarb.bmp", 7, 1);
	}
	CropsRenderer->SetSprite("Crops_Rhubarb.bmp", GrowStep);
	MaxGrowStep = 6;
}
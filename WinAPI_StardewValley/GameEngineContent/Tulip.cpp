#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Tulip.h"

Tulip::Tulip()
{

}

Tulip::~Tulip()
{

}

void Tulip::Start()
{
	ContentCrops::Start();
	CropsName = "Tulip.bmp";
	if (false == ResourcesManager::GetInst().IsLoadTexture("Crops_Tulip.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Crops\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Crops_Tulip.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Crops_Tulip.bmp", 6, 1);
	}
	CropsRenderer->SetSprite("Crops_Tulip.bmp", GrowStep);
	MaxGrowStep = 5;
}
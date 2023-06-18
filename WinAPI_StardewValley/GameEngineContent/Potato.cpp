#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Potato.h"

Potato::Potato()
{

}

Potato::~Potato()
{

}

void Potato::Start()
{
	ContentCrops::Start();
	CropsName = "Potato.bmp";
	if (false == ResourcesManager::GetInst().IsLoadTexture("Crops_Potato.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Crops\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Crops_Potato.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Crops_Potato.bmp", 7, 1);
	}
	CropsRenderer->SetSprite("Crops_Potato.bmp", GrowStep);
	MaxGrowStep = 6;
}

void Potato::Update(float _Delta)
{

}
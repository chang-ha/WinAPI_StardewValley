#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Cauliflower.h"

Cauliflower::Cauliflower()
{

}

Cauliflower::~Cauliflower()
{

}

void Cauliflower::Start()
{
	ContentCrops::Start();
	CropsName = "Cauliflower.bmp";
	if (false == ResourcesManager::GetInst().IsLoadTexture("Crops_Cauliflower.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Crops\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Crops_Cauliflower.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Crops_Cauliflower.bmp", 7, 1);
	}
	CropsRenderer->SetSprite("Crops_Cauliflower.bmp", GrowStep);
	MaxGrowStep = 6;
}
void Cauliflower::Update(float _Delta)
{

}
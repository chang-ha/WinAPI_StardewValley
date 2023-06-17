#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Garlic.h"

Garlic::Garlic()
{

}

Garlic::~Garlic()
{

}

void Garlic::Start()
{
	ContentCrops::Start();
	CropsName = "Garlic.bmp";
	if (false == ResourcesManager::GetInst().IsLoadTexture("Crops_Garlic.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Crops\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Crops_Garlic.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Crops_Garlic.bmp", 6, 1);
	}
	CropsRenderer->SetSprite("Crops_Garlic.bmp", GrowStep);
}
void Garlic::Update(float _Delta)
{

}
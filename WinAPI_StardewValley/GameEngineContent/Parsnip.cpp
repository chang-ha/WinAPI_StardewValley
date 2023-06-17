#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Parsnip.h"

Parsnip::Parsnip()
{

}

Parsnip::~Parsnip()
{

}

void Parsnip::Start()
{
	ContentCrops::Start();
	CropsName = "Parsnip.bmp";
	if (false == ResourcesManager::GetInst().IsLoadTexture("Crops_Parsnip.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Crops\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Crops_Parsnip.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Crops_Parsnip.bmp", 6, 1);
	}

	CropsRenderer->SetSprite("Crops_Parsnip.bmp", GrowStep);
}
void Parsnip::Update(float _Delta)
{

}
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Kale.h"
#include "ContentsEnum.h"
#include "ContentItem.h"
#include "GlobalValue.h"

Kale::Kale()
{

}

Kale::~Kale()
{

}

void Kale::Start()
{
	ContentCrops::Start();
	CropsName = "Kale.bmp";
	if (false == ResourcesManager::GetInst().IsLoadTexture("Crops_Kale.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Crops\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Crops_Kale.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Crops_Kale.bmp", 6, 1);
	}
	CropsRenderer->SetSprite("Crops_Kale.bmp", GrowStep);
	MaxGrowStep = 5;
}

void Kale::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_F5))
	{
		Grow();
	}

	if (MaxGrowStep != GrowStep)
	{
		return;
	}

	std::vector<GameEngineCollision*> _CollisionResult;
	if (true == CropsCollision->Collision(CollisionOrder::Sickle, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
	{
		ContentItem* Item = GetLevel()->CreateActor<ContentItem>(UpdateOrder::Inventory);
		Item->Init("Kale.bmp", ItemType::Crops);
		Item->SetPos(GetPos() + TILESIZE.Half() * RENDERRATIO);
		Item->RandomVector();
		Off();
	}
}

bool Kale::Harvest()
{
	return false;
}


#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Weed.h"
#include "ContentsEnum.h"
#include "ContentItem.h"
#include "GlobalValue.h"

Weed::Weed()
{

}

Weed::~Weed()
{

}

void Weed::Start()
{
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 3);
	std::string WeedName = "";
	switch (RandomValue)
	{
	case 0:
		WeedName = "Weed.bmp";
		break;
	case 1:
		WeedName = "Weed1.bmp";
		break;
	case 2:
		WeedName = "Weed2.bmp";
		break;
	case 3:
		WeedName = "Weed3.bmp";
		break;
	default:
		break;
	}

	ContentResources::Init(WeedName);
	if (false == ResourcesManager::GetInst().IsLoadTexture("Animation_Weed.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Resources\\");
		ResourcesManager::GetInst().CreateSpriteSheet("Animation_Weed", FilePath.PlusFilePath("Animation_Weed.bmp"), 7, 1);
	}
	Renderer->CreateAnimation("Death_Weed", "Animation_Weed", 0, 6, 0.1f, false);

	if (nullptr == GameEngineSound::FindSound("weeddeath.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("weeddeath.wav"));
	}
}

void Weed::Update(float _Delta)
{
	DeathAnimationUpdate();

	Collision->CollisionCallBack(CollisionOrder::Sickle, CollisionType::Rect, CollisionType::Rect,[](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			Weed* _CurWeed = dynamic_cast<Weed*>(_this->GetActor());
			_CurWeed->EffectPlayer = GameEngineSound::SoundPlay("weeddeath.wav");
			GameEngineLevel* CurLevel = _CurWeed->GetLevel();
			for (int x = 0; x < _CurWeed->ItemCount; x++)
			{
				ContentItem* Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
				Item->Init("Fiber.bmp", ItemType::Resources);
				Item->SetPos(_CurWeed->GetPos() + TILESIZE.Half() * RENDERRATIO);
				Item->RandomVector();
			}
			_CurWeed->WeedDeath();
		}
	);
}

void Weed::DeathAnimationUpdate()
{
	if (false == DeathValue)
	{
		return;
	}
	Renderer->ChangeAnimation("Death_Weed");

	if (true == Renderer->IsAnimationEnd())
	{
		Death();
	}
}

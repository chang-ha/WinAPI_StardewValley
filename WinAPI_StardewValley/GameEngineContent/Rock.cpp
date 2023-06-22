#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Rock.h"
#include "ContentsEnum.h"
#include "ContentItem.h"
#include "GlobalValue.h"

Rock::Rock()
{

}

Rock::~Rock()
{

}

void Rock::Start()
{
	// Rock_Small01.bmp
	std::string _FileName = "";
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 1);
	switch (RandomValue)
	{
	case 0:
		_FileName = "Rock_Small01.bmp";
		break;
	case 1:
		_FileName = "Rock_Small02.bmp";
		break;
	default:
		break;
	}

	ContentResources::Init(_FileName);
	if (nullptr == GameEngineSound::FindSound("rock.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("rock.wav"));
	}
}

void Rock::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _CollisionResult;
	if (true == Collision->Collision(CollisionOrder::PickAxe, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
	{
		EffectPlayer = GameEngineSound::SoundPlay("rock.wav");

		GameEngineLevel* CurLevel = GetLevel();
		for (int x = 0; x < ItemCount; x++)
		{
			ContentItem* Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
			Item->Init("Rock.bmp", ItemType::Resources);
			Item->SetPos(GetPos() + TILESIZE.Half() * RENDERRATIO);
			Item->RandomVector();
		}
		Death();
	}
}
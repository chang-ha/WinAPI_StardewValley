#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "SmallTree.h"
#include "ContentsEnum.h"
#include "ContentItem.h"
#include "GlobalValue.h"

SmallTree::SmallTree()
{

}

SmallTree::~SmallTree()
{

}

void SmallTree::Start()
{
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 1);
	switch (RandomValue)
	{
	case 0:
		ContentResources::Init("Tree_Small.bmp");
		break;
	case 1:
		ContentResources::Init("Tree_Small2.bmp");
		break;
	default:
		break;
	}
	if (nullptr == GameEngineSound::FindSound("axchop.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("axchop.wav"));
	}
}

void SmallTree::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _CollisionResult;
	if (true == Collision->Collision(CollisionOrder::Axe, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
	{
		EffectPlayer = GameEngineSound::SoundPlay("axchop.wav");

		GameEngineLevel* CurLevel = GetLevel();
		for (int x = 0; x < ItemCount; x++)
		{
			ContentItem* Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
			Item->Init("Wood.bmp", ItemType::Resources);
			Item->SetPos(GetPos() + TILESIZE.Half() * RENDERRATIO);
			Item->RandomVector();
		}
		Death();
	}
}
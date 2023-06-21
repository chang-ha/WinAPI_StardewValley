﻿#include <GameEngineCore/GameEngineLevel.h>
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

void SmallTree::Init(const std::string& _FileName)
{
	ContentResources::Init(_FileName);
	if (nullptr == GameEngineSound::FindSound("axchop.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("axchop.wav"));
	}
}

void SmallTree::Start()
{

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
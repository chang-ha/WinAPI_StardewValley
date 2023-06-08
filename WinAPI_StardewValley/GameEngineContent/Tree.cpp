#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Tree.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "Player.h"
#include "ContentItem.h"

Tree::Tree()
{

}

Tree::~Tree()
{

}

void Tree::Init(const std::string& _FileName)
{
	ContentResources::Init(_FileName);
	if (false == ResourcesManager::GetInst().IsLoadTexture("UpperPart_" + _FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Resources\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UpperPart_" + _FileName));
	}

	if (nullptr == GameEngineSound::FindSound("axchop.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("axchop.wav"));
	}
	UpperPart = CreateRenderer("UpperPart_" + _FileName, RenderOrder::PlayOver);
	UpperPart->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	UpperPart->SetRenderPos({ 0, -36 * RENDERRATIO });
}


void Tree::Start()
{
}

void Tree::Update(float _Delta)
{
	Hitten();

	if (Player::MainPlayer->GetPos().Y < GetPos().Y && UpperPart->GetOrder() < Player::MainPlayer->GetOrder())
	{
		UpperPart->SetOrder(static_cast<int>(RenderOrder::PlayOver));
	}
	else if (Player::MainPlayer->GetPos().Y > GetPos().Y && UpperPart->GetOrder() > Player::MainPlayer->GetOrder())
	{
		UpperPart->SetOrder(static_cast<int>(RenderOrder::BackGround));
	}

	static float PerTime = 1.0f;
	if (true == Collision->Collision(CollisionOrder::Axe, _CollisionResult, CollisionType::Rect, CollisionType::Rect) && 0.0f > PerTime)
	{
		IsHitten = true;
		EffectPlayer = GameEngineSound::SoundPlay("axchop.wav");
		PerTime = 1.0f;
		if (--Hp > 0)
		{
			return;
		}

		GameEngineLevel* CurLevel = GetLevel();
		for (int x = 0; x < ItemCount; x++)
		{
			ContentItem* Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
			Item->Init("Wood.bmp", ItemType::Resources);
			Item->SetPos(GetPos() + float4{x * RENDERRATIO * 8, 0});
		}

		ContentItem* Test = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
		Test->Init("Seed1.bmp", ItemType::Resources);
		Test->SetPos(GetPos());

		Test = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
		Test->Init("Seed2.bmp", ItemType::Resources);
		Test->SetPos(GetPos());

		Test = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
		Test->Init("Seed3.bmp", ItemType::Resources);
		Test->SetPos(GetPos());

		Test = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
		Test->Init("Seed4.bmp", ItemType::Resources);
		Test->SetPos(GetPos());

		Test = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
		Test->Init("Seed5.bmp", ItemType::Resources);
		Test->SetPos(GetPos());

		Test = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
		Test->Init("Seed6.bmp", ItemType::Resources);
		Test->SetPos(GetPos());

		Test = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
		Test->Init("Seed7.bmp", ItemType::Resources);
		Test->SetPos(GetPos());

		Death();
	}

	PerTime -= _Delta;
}

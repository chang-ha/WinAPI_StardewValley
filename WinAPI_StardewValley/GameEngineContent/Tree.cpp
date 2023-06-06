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

void Tree::Start()
{
}

void Tree::Update(float _Delta)
{
	if (Player::MainPlayer->GetPos().Y > GetPos().Y)
	{
		UpperPart->SetOrder(static_cast<int>(RenderOrder::BackGround));
	}
	else
	{
		UpperPart->SetOrder(static_cast<int>(RenderOrder::PlayOver));
	}

	if (true == Collision->Collision(CollisionOrder::Player, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineLevel* CurLevel = GetLevel();
		for (int x = 0; x < ItemCount; x++)
		{
			ContentItem* Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
			Item->Init("Wood.bmp", ItemType::Resources);
			Item->SetPos(GetPos());
		}
		Death();
	}
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
	UpperPart = CreateRenderer("UpperPart_" + _FileName, RenderOrder::PlayOver);
	UpperPart->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	UpperPart->SetRenderPos({0, -36 * RENDERRATIO});
}

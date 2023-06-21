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
	Renderer->SetRenderPos((TILESIZE.Half() - float4{0, 2})* RENDERRATIO);
	if (false == ResourcesManager::GetInst().IsLoadTexture("UpperPart_" + _FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Resources\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UpperPart_" + _FileName));
	}

	if (nullptr == GameEngineSound::FindSound("axchop.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("axchop.wav"));
	}
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("UpperPart_" + _FileName);
	UpperPart = CreateRenderer("UpperPart_" + _FileName, RenderOrder::Play);
	UpperPart->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	UpperPart->SetRenderPos((TILESIZE.Half() - float4{ 0, 38 }) * RENDERRATIO);
	UpperPart->SetYPivot(- (TILESIZE.Half().Y - 38)* RENDERRATIO);
}


void Tree::Start()
{
}

void Tree::Update(float _Delta)
{
	Hitten();

	static float PerTime = 0.5f;
	if (true == Collision->Collision(CollisionOrder::Axe, _CollisionResult, CollisionType::Rect, CollisionType::Rect) && 0.0f > PerTime)
	{
		IsHitten = true;
		EffectPlayer = GameEngineSound::SoundPlay("axchop.wav");
		PerTime = 0.5f;
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
			Item->RandomVector();
		}
		Death();
	}

	PerTime -= _Delta;
}

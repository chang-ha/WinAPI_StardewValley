#define HITTIME 0.5f

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
	ShadowRenderer->SetRenderPos((TILESIZE.Half() - float4{ 0, 2 }) * RENDERRATIO);
	if (false == ResourcesManager::GetInst().IsLoadTexture("UpperPart_" + _FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Resources\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UpperPart_" + _FileName));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Mask_UpperPart_" + _FileName));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Shadow_UpperPart_Tree.bmp"));
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
	UpperPart->SetRenderPos((TILESIZE.Half() + float4{ 0, 7 }) * RENDERRATIO);
	UpperPart->SetYPivot(- (TILESIZE.Half().Y + 7)* RENDERRATIO);
	UpperPart->SetMaskTexture("Mask_UpperPart_" + _FileName);

	Texture = ResourcesManager::GetInst().FindTexture("Shadow_UpperPart_Tree.bmp");
	UpperPartShadow = CreateRenderer("Shadow_UpperPart_Tree.bmp", RenderOrder::Shadow);
	UpperPartShadow->SetAlpha(120);
	UpperPartShadow->SetRenderPos(TILESIZE.Half() + float4{4, 8} * RENDERRATIO);
	UpperPartShadow->SetRenderScale(Texture->GetScale() * RENDERRATIO);
}


void Tree::Start()
{
}

void Tree::Update(float _Delta)
{
	Collision->CollisionCallBack(CollisionOrder::Axe, CollisionType::Rect, CollisionType::Rect, [](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			Tree* _CurTree = dynamic_cast<Tree*>(_this->GetActor());
			_CurTree->SetIsHitten(true);
			_CurTree->EffectPlayer = GameEngineSound::SoundPlay("axchop.wav");
			_CurTree->PlusHp(-1);
			if (_CurTree->GetHp() > 0)
			{
				return;
			}

			GameEngineLevel* CurLevel = _CurTree->GetLevel();
			for (int x = 0; x < _CurTree->ItemCount; x++)
			{
				ContentItem* Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
				Item->Init("Wood.bmp", ItemType::Resources);
				Item->SetPos(_CurTree->GetPos() + TILESIZE.Half() * RENDERRATIO);
				Item->RandomVector();
			}
			_CurTree->Death();
		}
	);

	Hitten(_Delta);
}

void Tree::Hitten(float _Delta)
{
	static float PerTime = HITTIME;
	if (true == IsHitten && 0.0f >= PerTime)
	{
		switch (HittenStep)
		{
		case 0:
			++HittenStep;
			UpperPart->SetAngle(-1.0f);
			break;
		case 1:
			++HittenStep;
			UpperPart->SetAngle(1.0f);
			break;
		case 2:
			++HittenStep;
			UpperPart->SetAngle(0.0f);
			HittenStep = 0;
			IsHitten = false;
		default:
			break;
		}
		PerTime = HITTIME;
	}
	PerTime -= _Delta;
}

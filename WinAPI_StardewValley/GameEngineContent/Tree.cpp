#define FALLSPEED 1.0f
#define HITTENANGLE 0.25f

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
			if (_CurTree->GetHp() > 3)
			{
				if (Player::MainPlayer->GetPos().X > _CurTree->GetPos().X)
				{
					_CurTree->AngleValue = -2.0f;
				}
				else
				{
					_CurTree->AngleValue = 2.0f;
				}
				return;
			}
			_CurTree->SetIsFall(true);
		}
	);

	Hitten(_Delta);
	FallDown(_Delta);

	if (0 >= Hp)
	{
		ContentItem* Item = GetLevel()->CreateActor<ContentItem>(UpdateOrder::Inventory);
		Item->Init("Wood.bmp", ItemType::Resources);
		Item->SetPos(GetPos() + TILESIZE.Half() * RENDERRATIO);
		Item->RandomVector();
		this->Death();
	}

}

void Tree::Hitten(float _Delta)
{
	if (nullptr == UpperPart)
	{
		return;
	}

	if (true == IsHitten)
	{
		if (AngleValue == CurAngle)
		{
			AngleValue = -AngleValue / 2.0f;
			if (HITTENANGLE > abs(AngleValue))
			{
				AngleValue = 0.0f;
			}
		}
		else if (0 > AngleValue && AngleValue != CurAngle)
		{
			CurAngle -= HITTENANGLE;
			UpperPart->SetAngle(CurAngle);
		}
		else if (0 < AngleValue && AngleValue != CurAngle)
		{
			CurAngle += HITTENANGLE;
			UpperPart->SetAngle(CurAngle);
		}
	}
}

void Tree::FallDown(float _Delta)
{
	if (false == IsFall || nullptr == UpperPart)
	{
		return;
	}
	UpperPart->SetRenderPos((TILESIZE.Half() + float4{ 0, 3 }) * RENDERRATIO);
	IsHitten = false;

	if (Player::MainPlayer->GetPos().X > GetPos().X)
	{
		AngleValue = -90.0f;
		ItemPos = - TILESIZE.X * RENDERRATIO * 3;
	}
	else
	{
		AngleValue = 90.0f;
		ItemPos = TILESIZE.X * RENDERRATIO * 3;
	}

	if (0 > AngleValue && AngleValue != CurAngle)
	{
		AngleSpeed -= FALLSPEED * _Delta;
		CurAngle += AngleSpeed;
		UpperPart->SetAngle(CurAngle);
	}
	else if (0 < AngleValue && AngleValue != CurAngle)
	{
		AngleSpeed += FALLSPEED * _Delta;
		CurAngle += AngleSpeed;
		UpperPart->SetAngle(CurAngle);
	}

	if (90 <= abs(CurAngle) && nullptr != UpperPart)
	{
		GameEngineLevel* CurLevel = GetLevel();
		for (int x = 0; x < ItemCount; x++)
		{
			ContentItem* Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
			Item->Init("Wood.bmp", ItemType::Resources);
			Item->SetPos(GetPos() + TILESIZE.Half() * RENDERRATIO + float4{ItemPos, 0});
			Item->RandomVector();
		}
		UpperPart->Death();
		UpperPartShadow->Death();
		CurAngle = 0;
		UpperPart = nullptr;
		UpperPartShadow = nullptr;
		IsFall = false;
	}
}


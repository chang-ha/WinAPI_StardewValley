#define CASESPEED 0.05f

#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ShippingBin.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

#include "Player.h"

ShippingBin::ShippingBin()
{

}

ShippingBin::~ShippingBin()
{

}

void ShippingBin::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Shipping_Bin.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Building\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Shipping_Bin.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Shipping_Bin_Case", FilePath.PlusFilePath("Shipping_Bin_Case.bmp"), 13, 1);
	}

	if (nullptr == GameEngineSound::FindSound("doorCreak.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("doorCreak.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("doorCreakReverse.wav"));
	}
	// ShippingBox Texture
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("Shipping_Bin.bmp");
	BodyRenderer = CreateRenderer(RenderOrder::Play);
	BodyRenderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	BodyRenderer->SetTexture("Shipping_Bin.bmp");
	BodyRenderer->SetRenderPos(float4{0, 0.5} *RENDERRATIO);

	// Collision
	Collision = CreateCollision(CollisionOrder::Map);
	Collision->SetCollisionScale(Texture->GetScale() * RENDERRATIO * 2);

	// Case Animation
	CaseRenderer = CreateRenderer(RenderOrder::PlayOver);
	CaseRenderer->SetRenderPos(float4{0, -10} *RENDERRATIO);
	CaseRenderer->CreateAnimation("Shipping_Bin_Case_Idle", "Shipping_Bin_Case", 0, 0);
	CaseRenderer->CreateAnimation("Shipping_Bin_Case_Open", "Shipping_Bin_Case", 0, 12, CASESPEED, false);
	CaseRenderer->CreateAnimation("Shipping_Bin_Case_Close", "Shipping_Bin_Case", 12, 0, CASESPEED, false);
	CaseRenderer->ChangeAnimation("Shipping_Bin_Case_Idle");
	CaseRenderer->SetScaleRatio(RENDERRATIO);
}

void ShippingBin::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _CollisionResult;
	if (true == Collision->Collision(CollisionOrder::Player, _CollisionResult, CollisionType::Rect, CollisionType::Rect) && false == IsOpen)
	{
		CaseRenderer->ChangeAnimation("Shipping_Bin_Case_Open");
		IsOpen = true;
		EffectPlayer = GameEngineSound::SoundPlay("doorCreak.wav");
	}
	else if(false == Collision->Collision(CollisionOrder::Player, _CollisionResult, CollisionType::Rect, CollisionType::Rect) && true == IsOpen)
	{
		CaseRenderer->ChangeAnimation("Shipping_Bin_Case_Close");
		IsOpen = false;
		EffectPlayer = GameEngineSound::SoundPlay("doorCreakReverse.wav");
	}
}
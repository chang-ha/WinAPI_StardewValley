#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ShippingBin.h"
#include "ContentsEnum.h"

#define CASESPEED 0.05f

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

		// Shipping Can Texture
		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Shipping_Bin.bmp"));
		BodyRenderer = CreateRenderer(RenderOrder::PlayBelow);
		BodyRenderer->SetRenderScale(Texture->GetScale() * 3);

		// Open & Close Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Shipping_Bin_Case", FilePath.PlusFilePath("Shipping_Bin_Case.bmp"), 13, 1);
		CaseRenderer = CreateRenderer(RenderOrder::PlayOver);
		CaseRenderer->CreateAnimation("Shipping_Bin_Case_Idle", "Shipping_Bin_Case", 0, 0);
		CaseRenderer->CreateAnimation("Shipping_Bin_Case_Open", "Shipping_Bin_Case", 0, 12, CASESPEED, false);
		CaseRenderer->CreateAnimation("Shipping_Bin_Case_Close", "Shipping_Bin_Case", 12, 0, CASESPEED, false);
		CaseRenderer->SetScaleRatio(3);

		// Collision
		BodyCollision = CreateCollision(CollisionOrder::Map);
		BodyCollision->SetCollisionScale(Texture->GetScale() * 3 * 2);
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
	BodyRenderer->SetTexture("Shipping_Bin.bmp");
	BodyRenderer->SetRenderPos(float4{0, 0.5} * 3);
	CaseRenderer->ChangeAnimation("Shipping_Bin_Case_Idle");
	CaseRenderer->SetRenderPos(float4{0, -10} * 3);
}

void ShippingBin::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _CollisionResult;
	if (true == BodyCollision->Collision(CollisionOrder::Player, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
	{
		CaseRenderer->ChangeAnimation("Shipping_Bin_Case_Open");
		IsOpen = true;
		// EffectPlayer.Stop();
		// EffectPlayer = GameEngineSound::SoundPlay("doorCreak.wav");
	}
	else if(true == IsOpen)
	{
		CaseRenderer->ChangeAnimation("Shipping_Bin_Case_Close");
		IsOpen = false;
		// EffectPlayer.Stop();
		// EffectPlayer = GameEngineSound::SoundPlay("doorCreakReverse.wav");
	}
}
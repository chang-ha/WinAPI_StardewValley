#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Player.h"
#include "ContentsEnum.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Player_body_01.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Player\\");
		ResourcesManager::GetInst().CreateSpriteFolder("Player_body", FilePath.PlusFilePath("Player_body"));
		ResourcesManager::GetInst().CreateSpriteFolder("Player_hair", FilePath.PlusFilePath("Player_hair"));
		ResourcesManager::GetInst().CreateSpriteFolder("Player_arm", FilePath.PlusFilePath("Player_arm"));
		ResourcesManager::GetInst().CreateSpriteFolder("Player_shirt", FilePath.PlusFilePath("Player_shirt"));
		ResourcesManager::GetInst().CreateSpriteFolder("Player_pants", FilePath.PlusFilePath("Player_pants"));
		ResourcesManager::GetInst().CreateSpriteFolder("Player_hat", FilePath.PlusFilePath("Player_hat"));

		BodyRenderer = CreateRenderer(RenderOrder::Play);
		// HairRenderer = CreateRenderer(RenderOrder::Play);
		ArmRenderer = CreateRenderer(RenderOrder::Play);
		// ShirtRenderer = CreateRenderer(RenderOrder::Equip);
		// PantsRenderer = CreateRenderer(RenderOrder::Equip);
		// HatRenderer = CreateRenderer(RenderOrder::Equip);
	}

	{
		BodyRenderer->CreateAnimation("Idle", "Player_body", 0, 2);
		BodyRenderer->SetScaleRatio(3.7f);
		BodyRenderer->ChangeAnimation("Idle");
	}

	//{
	//	HairRenderer = CreateRenderer("Player_hair_75.bmp", RenderOrder::Play);
	//	HairRenderer->SetTexture("Player_hair_75.bmp");
	//	HairRenderer->SetScaleRatio(3.7f);
	//}

	{
		ArmRenderer->CreateAnimation("Idle", "Player_arm", 0, 2);
		ArmRenderer->SetScaleRatio(3.7f);
		ArmRenderer->ChangeAnimation("Idle");
	}

	//{
	//	ShirtRenderer = CreateRenderer("shirts.bmp", RenderOrder::Equip);
	//	ShirtRenderer->SetTexture("shirts.bmp");
	//	ShirtRenderer->SetRenderPos({ 0,8 });
	//	ShirtRenderer->SetRenderScale(ShirtRenderer->GetTextureScale() * 3.7f);
	//}

	//{
	//	PantsRenderer = CreateRenderer("pants.bmp", RenderOrder::Equip);
	//	PantsRenderer->SetTexture("pants.bmp");
	//	PantsRenderer->SetRenderScale(PantsRenderer->GetTextureScale() * 3.7f);
	//}

	//{
	//	HatRenderer = CreateRenderer("Player_hat_05.bmp", RenderOrder::Equip);
	//	HatRenderer->SetTexture("Player_hat_05.bmp");
	//	HatRenderer->SetRenderPos({0,-32});
	//	HatRenderer->SetRenderScale(HatRenderer->GetTextureScale() * 3.7f);
	//}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	SetPos(WinScale.Half());
}
void Player::Update(float _Delta)
{
	float Speed = 1000.0f;

	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
	}

	// MousePos
	// float4 Pos = GameEngineWindow::MainWindow.GetMousePos();
	AddPos(MovePos);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	float4 BackScale;

	if (true)
	{
		GetLevel()->GetMainCamera()->AddPos(MovePos);
	}
	
}
void Player::Render()
{
}
void Player::Release()
{

}
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
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_body\\Player_body_01.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_hair\\Player_hair_75.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_arm\\Player_arm_01.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_shirt\\shirts.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_pants\\pants.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_hat\\Player_hat_05.bmp"));
	}

	{
		BodyRenderer = CreateRenderer("Player_body_01.bmp", RenderOrder::Play);
		BodyRenderer->SetTexture("Player_body_01.bmp");
		BodyRenderer->SetScaleRatio(3.7f);
		// BodyRenderer->SetRenderScale(BodyRenderer->GetTextureScale()*3.7f);
	}

	{
		HairRenderer = CreateRenderer("Player_hair_75.bmp", RenderOrder::Play);
		HairRenderer->SetTexture("Player_hair_75.bmp");
		HairRenderer->SetScaleRatio(3.7f);
	}

	{
		ArmRenderer = CreateRenderer("Player_arm_01.bmp", RenderOrder::Play);
		ArmRenderer->SetTexture("Player_arm_01.bmp");
		ArmRenderer->SetRenderScale(ArmRenderer->GetTextureScale() * 3.7f);
	}

	{
		ShirtRenderer = CreateRenderer("shirts.bmp", RenderOrder::Equip);
		ShirtRenderer->SetTexture("shirts.bmp");
		ShirtRenderer->SetRenderPos({ 0,8 });
		ShirtRenderer->SetRenderScale(ShirtRenderer->GetTextureScale() * 3.7f);
	}

	{
		PantsRenderer = CreateRenderer("pants.bmp", RenderOrder::Equip);
		PantsRenderer->SetTexture("pants.bmp");
		PantsRenderer->SetRenderScale(PantsRenderer->GetTextureScale() * 3.7f);
	}

	{
		HatRenderer = CreateRenderer("Player_hat_05.bmp", RenderOrder::Equip);
		HatRenderer->SetTexture("Player_hat_05.bmp");
		HatRenderer->SetRenderPos({0,-32});
		HatRenderer->SetRenderScale(HatRenderer->GetTextureScale() * 3.7f);
	}

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
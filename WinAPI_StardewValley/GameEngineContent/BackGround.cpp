#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "BackGround.h"
#include "ContentsEnum.h"
BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
}

void BackGround::Update(float _Delta)
{
//	GetLevel()->GetMainCamera()->AddPos({0, -30.0f*_Delta});
}

void BackGround::Render()
{

}

void BackGround::Release()
{

}

void BackGround::Init(const std::string& _FileName)
{
	FileName = _FileName;
	if (false == ResourcesManager::GetInst().IsLoadTexture(FileName))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Title\\");
		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(FileName));
		Scale = Text->GetScale();
		// Text = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title_LeftBg.bmp"));
		// Text = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title_RightBg.bmp"));
	}
	GameEngineRenderer* Renderer = CreateRenderer(FileName, RenderOrder::BackGround);
	float4 WinPos = GameEngineWindow::MainWindow.GetScale();
	WinPos = WinPos.Half(); // 1280 720 >> 640 360
	Scale = Scale.Half(); // 1920 1200 >> 960 600
	WinPos.Y = static_cast<float>((Scale.Y - WinPos.Y) / 2); // (600 - 360) / 2
	WinPos.X += 320.0f; // (600 - 360) / 2
	SetPos(WinPos);
	{
		// GameEngineRenderer* Ptr = CreateRenderer("Title_LeftBg.bmp", RenderOrder::Play);
		// float4 SetPos = WinPos;
		// SetPos.X -= 640;
		// Ptr->SetRenderPos(WinPos);
	}

	{
		// GameEngineRenderer* Ptr = CreateRenderer("Title_RightBg.bmp", RenderOrder::Play);
		// float4 SetPos = WinPos;
		// SetPos.X += 640;
		// Ptr->SetRenderPos(WinPos);
	}

}
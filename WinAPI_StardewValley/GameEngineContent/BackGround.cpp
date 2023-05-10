#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>

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
		float4 Scale = Text->GetScale();
	}
	GameEngineRenderer* Renderer = CreateRenderer(FileName, RenderOrder::BackGround);
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	WinScale = WinScale.Half(); // 640 360
	WinScale.Y = static_cast<float>(120); // (600 - 360) / 2
	SetPos(WinScale);
}
#include "BackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	SetPos({ 680, 384 });
}

void BackGround::Update(float _Delta)
{

}

void BackGround::Render()
{
	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture(FileName);
	if (nullptr == FindTexture)
	{
		return;
	}
	float4 TestScale = GetScale();
	TestScale.X *= 0.71f;
	TestScale.Y *= 0.648f;
	BackBuffer->TransCopy(FindTexture, GetPos(), TestScale, { 0, 0 }, FindTexture->GetScale(), (255, 0, 255));
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
		FilePath.MoveChild("Resources\\Textures\\Title\\" + FileName);
		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
		float4 Scale = Text->GetScale();
		SetScale(Scale);
	}
}
#include "TitleBird.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>

TitleBird::TitleBird()
{

}

TitleBird::~TitleBird()
{

}

void TitleBird::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Title_bird01.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Title\\Title_bird01.bmp");
		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	SetScale({ 26, 18 });
}
void TitleBird::Update(float _Delta) 
{
	AddPos({-10.0f * _Delta, 0.0f});
}
void TitleBird::Render()
{
	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture("Title_bird01.bmp");
	if (nullptr == FindTexture)
	{
		return;
	}
	BackBuffer->TransCopy(FindTexture, GetPos(), GetScale(), { 0, 0}, FindTexture->GetScale());
}
void TitleBird::Release()
{

}
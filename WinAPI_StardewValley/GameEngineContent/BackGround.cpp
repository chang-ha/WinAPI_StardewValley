#include "BackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

BackGround::BackGround()
{
	int a = 0;
}

BackGround::~BackGround()
{
	int a = 0;
}

void BackGround::Start()
{
	SetPos({960, 540});
}

void BackGround::Update(float _Delta)
{

}

void BackGround::Render()
{
	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture(FileName);
	BackBuffer->BitCopy(FindTexture, GetPos());
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
		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}
}
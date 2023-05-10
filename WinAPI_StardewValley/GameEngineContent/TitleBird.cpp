#include "TitleBird.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "ContentsEnum.h"
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
		FilePath.MoveChild("Resources\\Textures\\Title\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title_bird01.bmp"));
	}
	GameEngineRenderer* Ptr = CreateRenderer("Title_bird01.bmp", RenderOrder::Play);
}
void TitleBird::Update(float _Delta) 
{
	AddPos({-10.0f * _Delta, 0.0f});
}
void TitleBird::Render()
{
}
void TitleBird::Release()
{

}
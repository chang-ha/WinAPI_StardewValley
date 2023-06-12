#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "FadeObject.h"

FadeObject::FadeObject()
{

}

FadeObject::~FadeObject()
{

}


void FadeObject::Start()
{
	// if (false == ResourcesManager::GetInst().IsLoadTexture("FADE.bmp"))
	// {
	// 	GameEnginePath FilePath;
	// 	FilePath.SetCurrentPath();
	// 	FilePath.MoveParentToExistsChild("ContentsResources");
	// 
	// 	GameEnginePath FolderPath = FilePath;
	// 
	// 	FilePath.MoveChild("ContentsResources\\Texture\\");
	// 
	// 	ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("FADE.bmp"));
	// }
	// 
	// GameEngineRenderer* Render = CreateUIRenderer(200);
	// Render->SetTexture("FADE.bmp");
	// Render->SetRenderPos(GameEngineWindow::MainWindow.GetScale().Half());
	// Render->SetRenderScale(GameEngineWindow::MainWindow.GetScale());
}


#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "ContentsEnum.h"
#include "ContentMouse.h"

ContentMouse* ContentMouse::MainMouse = nullptr;

ContentMouse::ContentMouse()
{
}

ContentMouse::~ContentMouse()
{

}

void ContentMouse::Start()
{
	MouseRenderer = CreateUIRenderer(RenderOrder::UIMouse);
	MouseCollision = CreateCollision(CollisionOrder::UIMouse);
	ItemRenderer = CreateUIRenderer(RenderOrder::UI);
	ItemRenderer->Off();
	if (false == ResourcesManager::GetInst().IsLoadTexture("Cursor01.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\UI\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Cursor01.bmp"));
	}
	Texture = ResourcesManager::GetInst().FindTexture("Cursor01.bmp");
	MouseRenderer->SetTexture("Cursor01.bmp");
	MouseRenderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	MouseRenderer->SetRenderPos(Texture->GetScale().Half() * RENDERRATIO);
	MouseCollision->SetCollisionScale(Texture->GetScale() * RENDERRATIO);
}

void ContentMouse::Update(float _Delta)
{
	SetPos(GameEngineWindow::MainWindow.GetMousePos());
	MouseCollision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos());
}

float4 ContentMouse::GetMousePos()
{
	return GetLevel()->GetMainCamera()->GetPos() + GetPos();
}


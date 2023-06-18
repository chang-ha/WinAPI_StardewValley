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

	if (false == ResourcesManager::GetInst().IsLoadTexture("Cursor01.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\UI\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Cursor01.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Cursor03.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Cursor04.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Cursor07.bmp"));
	}
	// Mouse Renderer
	Texture = ResourcesManager::GetInst().FindTexture("Cursor01.bmp");
	MouseRenderer = CreateUIRenderer(RenderOrder::UIMouse);
	MouseRenderer->SetTexture("Cursor01.bmp");
	MouseRenderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	MouseRenderer->SetRenderPos(Texture->GetScale().Half() * RENDERRATIO);

	// Mouse Collision
	MouseCollision = CreateCollision(CollisionOrder::UIMouse);
	MouseCollision->SetCollisionScale(TILESIZE * RENDERRATIO * 0.8f);

	// Mouse Item Renderer
	ItemRenderer = CreateUIRenderer(RenderOrder::UI);
	ItemRenderer->SetRenderPos(TILESIZE * RENDERRATIO);
	ItemRenderer->SetRenderScale(TILESIZE * RENDERRATIO);
	ItemRenderer->Off();
}

void ContentMouse::Update(float _Delta)
{
	SetPos(GameEngineWindow::MainWindow.GetMousePos());
	MouseCollision->SetCollisionPos(GetLevel()->GetMainCamera()->GetPos());
	
	std::vector<GameEngineCollision*> _CollisionResult;
	if (true == MouseCollision->Collision(CollisionOrder::Crops, _CollisionResult, CollisionType::Rect, CollisionType::Rect))
	{

	}
}

float4 ContentMouse::GetMousePos()
{
	return GetLevel()->GetMainCamera()->GetPos() + GetPos();
}


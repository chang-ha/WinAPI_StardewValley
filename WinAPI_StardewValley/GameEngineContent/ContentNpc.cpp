#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentNpc.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "ContentMouse.h"

ContentNpc::ContentNpc()
{

}

ContentNpc::~ContentNpc()
{

}

void ContentNpc::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Npc_Pierre_01.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Npc\\Pierre\\");
		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Npc_Pierre_01.bmp"));
		NpcRenderer = CreateRenderer(RenderOrder::Play);
		NpcRenderer->SetTexture("Npc_Pierre_01.bmp");
		NpcRenderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	}
	NpcCollision = CreateCollision(CollisionOrder::Npc);
	NpcCollision->SetCollisionScale(TILESIZE * RENDERRATIO);
}

void ContentNpc::Update(float _Delta)
{
	if (true == NpcCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect))
	{

	}
}
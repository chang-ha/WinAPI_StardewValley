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
		FilePath.MoveChild("Resources\\Textures\\Npc\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Npc_Pierre_01.bmp"));
	}
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("Npc_Pierre_01.bmp");
	NpcRenderer = CreateRenderer("Npc_Pierre_01.bmp", RenderOrder::Play);
	NpcRenderer->SetRenderScale(Texture->GetScale() * RENDERRATIO);
	NpcCollision = CreateCollision(CollisionOrder::Npc);
	NpcCollision->SetCollisionPos(float4{ 0, 9 } *RENDERRATIO);
	NpcCollision->SetCollisionScale(TILESIZE * RENDERRATIO);
}

void ContentNpc::Update(float _Delta)
{
}
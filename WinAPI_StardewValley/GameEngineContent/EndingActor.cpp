#define ANISPEED 0.08f
#define MOVESPEED 50.0f

#include <GameEngineCore/GameEngineRenderer.h>

#include <GameEngineCore/ResourcesManager.h>

#include "EndingActor.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

EndingActor::EndingActor()
{

}

EndingActor::~EndingActor()
{

}

void EndingActor::Init(const std::string& _ActorName)
{

}

void EndingActor::InitAnimation(const std::string& _ActorName)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_ActorName + ".bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Npc\\");
		ResourcesManager::GetInst().CreateSpriteSheet(_ActorName, FilePath.PlusFilePath(_ActorName + ".bmp"), 5, 1);
	}
	GameEngineRenderer* Renderer = CreateRenderer(RenderOrder::UI);
	Renderer->CreateAnimation("Idle", _ActorName, 0, 4, ANISPEED, true);
	Renderer->SetScaleRatio(2.0f);
	Renderer->ChangeAnimation("Idle");
}

void EndingActor::Start()
{

}

void EndingActor::Update(float _Delta)
{
	AddPos({- MOVESPEED * _Delta, 0});
}
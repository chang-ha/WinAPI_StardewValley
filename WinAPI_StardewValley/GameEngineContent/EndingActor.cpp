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

void EndingActor::InitAnimation(const std::string& _ActorName, float _AniSpeed)
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
	Renderer->CreateAnimation("Idle", _ActorName, 0, 4, _AniSpeed, true);
	Renderer->SetScaleRatio(2.0f);
	Renderer->ChangeAnimation("Idle");
}

void EndingActor::InitAnimation(const std::string& _ActorName, const std::string& _TextName, float _AniSpeed)
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
	Renderer->CreateAnimation("Idle", _ActorName, 0, 4, _AniSpeed, true);
	Renderer->SetScaleRatio(2.0f);
	Renderer->ChangeAnimation("Idle");

	GameEngineRenderer* TextRenderer = CreateRenderer(RenderOrder::UI);
	TextRenderer->SetText(_TextName, 30, "Sandoll ¹Ì»ý");
	TextRenderer->ChangeTextColor(RGB(255, 255, 255));
	TextRenderer->SetRenderPos({- 16, 32});
}


void EndingActor::Start()
{

}

void EndingActor::Update(float _Delta)
{
	AddPos({- Speed * _Delta, 0});

	if (-30 > GetPos().X)
	{
		Death();
	}
}
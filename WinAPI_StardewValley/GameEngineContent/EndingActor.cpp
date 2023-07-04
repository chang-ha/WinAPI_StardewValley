#include <GameEngineBase/GameEngineRandom.h>

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
	if (false == ResourcesManager::GetInst().IsLoadTexture(_ActorName + ".bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Ending\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_ActorName + ".bmp"));
	}
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_ActorName + ".bmp");
	GameEngineRenderer* Renderer = CreateRenderer(_ActorName + ".bmp", RenderOrder::UI);
	Renderer->SetRenderScale(Texture->GetScale() * 2.0f);
}

void EndingActor::InitAnimation(const std::string& _ActorName, float _AniSpeed, float _Speed, int _FramCount)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_ActorName + ".bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Ending\\");
		ResourcesManager::GetInst().CreateSpriteSheet(_ActorName, FilePath.PlusFilePath(_ActorName + ".bmp"), _FramCount, 1);
	}
	GameEngineRenderer* Renderer = CreateRenderer(RenderOrder::UI);
	Renderer->CreateAnimation("Idle", _ActorName, 0, _FramCount - 1, _AniSpeed, true);
	Renderer->SetScaleRatio(2.0f);
	int StartFrame = GameEngineRandom::MainRandom.RandomInt(0, 1);
	Renderer->ChangeAnimation("Idle", StartFrame);

	Speed = _Speed;
}

void EndingActor::InitAnimation(const std::string& _ActorName, const std::string& _TextName, float _AniSpeed, float _Speed)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_ActorName + ".bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Ending\\");
		ResourcesManager::GetInst().CreateSpriteSheet(_ActorName, FilePath.PlusFilePath(_ActorName + ".bmp"), 4, 1);
	}
	GameEngineRenderer* Renderer = CreateRenderer(RenderOrder::UI);
	Renderer->CreateAnimation("Idle", _ActorName, 0, 3, _AniSpeed, true);
	Renderer->SetScaleRatio(2.0f);
	Renderer->ChangeAnimation("Idle");

	GameEngineRenderer* TextRenderer = CreateRenderer(RenderOrder::UI);
	TextRenderer->SetText(_TextName, 30, "Sandoll ¹Ì»ý");
	TextRenderer->ChangeTextColor(RGB(255, 255, 255));
	TextRenderer->SetRenderPos({- 20, 32});

	Speed = _Speed;
}


void EndingActor::Start()
{

}

void EndingActor::Update(float _Delta)
{
	AddPos({- Speed * _Delta, 0});

	if (-GlobalValue::WinScale.X > GetPos().X)
	{
		Death();
	}
}
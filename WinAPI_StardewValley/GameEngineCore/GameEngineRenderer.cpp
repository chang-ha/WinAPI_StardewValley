#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>

#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineLevel.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "ResourcesManager.h"
#include "GameEngineSprite.h"

GameEngineRenderer::GameEngineRenderer()
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::SetTexture(const std::string& _Name)
{
	Texture = ResourcesManager::GetInst().FindTexture(_Name);
	if (nullptr == Texture)
	{
		MsgBoxAssert(_Name + "존재하지 않는 Texture를 세팅하려고 했습니다.");
	}
	SetCopyPos(float4::ZERO);
	SetCopyScale(Texture->GetScale());
	if (false == ScaleCheck)
	{
		SetRenderScaleToTexture();
	}
}

void GameEngineRenderer::SetSprite(const std::string& _Name, size_t _Index /*= 0*/)
{
	Sprite = ResourcesManager::GetInst().FindSprite(_Name);
	if (nullptr == Sprite)
	{
		MsgBoxAssert(_Name + "존재하지 않은 Sprite를 세팅하려고 했습니다.");
	}
	const GameEngineSprite::Sprite& SpriteInfo = Sprite->GetSprite(_Index);
	Texture = SpriteInfo.BaseTexture;
	SetCopyPos(SpriteInfo.RenderPos);
	SetCopyScale(SpriteInfo.RenderScale);
}

void GameEngineRenderer::SetRenderScaleToTexture()
{
	if (nullptr != Texture)
	{
		RenderScale = Texture->GetScale();
	}
	ScaleCheck = false;
}


void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _DeltaTime)
{
	if (nullptr != CurAnimation)
	{
		CurAnimation->CurInter -= _DeltaTime;
		if (0.0f >= CurAnimation->CurInter)
		{
			CurAnimation->CurInter 
				= CurAnimation->Inters[CurAnimation->CurFrame];
			++CurAnimation->CurFrame;

			if (CurAnimation->CurFrame > abs(static_cast<int>(CurAnimation->EndFrame - CurAnimation->StartFrame)))
			{
				if (true == CurAnimation->Loop)
				{
					CurAnimation->CurFrame = 0;
				}
				else
				{
					--CurAnimation->CurFrame;
				}
			}

		}

		size_t Frame = CurAnimation->Frames[CurAnimation->CurFrame];
		Sprite = CurAnimation->Sprite;
		const GameEngineSprite::Sprite& SpriteInfo = Sprite->GetSprite(Frame);
		Texture = SpriteInfo.BaseTexture;
		SetCopyPos(SpriteInfo.RenderPos);
		SetCopyScale(SpriteInfo.RenderScale);

		if (false == ScaleCheck)
		{
			SetRenderScale(SpriteInfo.RenderScale * ScaleRatio);
		}
	}

	if (nullptr == Texture)
	{
		MsgBoxAssert("이미지를 세팅하지 않은 랜더러 입니다.");
	}

	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	BackBuffer->TransCopy(Texture, GetActor()->GetPos() + RenderPos - _Camera->GetPos(), RenderScale, CopyPos, CopyScale);
}

GameEngineRenderer::Animation* GameEngineRenderer::FindAnimation(const std::string& _AnimationName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);
	std::map<std::string, Animation>::iterator FindIter = AllAnimation.find(UpperName);
	if (AllAnimation.end() == FindIter)
	{
		return nullptr;
	}
	return &FindIter->second;
}


void GameEngineRenderer::CreateAnimation(const std::string& _AnimationName, const std::string& _SpriteName
	, size_t _Start /*= -1*/, size_t _End /*= -1*/, float _Inter /*= 0.1f*/, bool _Loop /*= true*/)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);
	if (nullptr != FindAnimation(UpperName))
	{
		MsgBoxAssert(_AnimationName + "이미 존재하는 애니메이션입니다.");
		return;
	}

	GameEngineSprite* Sprite = ResourcesManager::GetInst().FindSprite(_SpriteName);
	if (nullptr == Sprite)
	{
		MsgBoxAssert(_SpriteName + "은 존재하지 않는 스프라이트입니다.");
		return;
	}

	GameEngineRenderer::Animation& Animation = AllAnimation[UpperName];
	Animation.Sprite = Sprite;
	if (-1 != _Start)
	{
		Animation.StartFrame = _Start;
	}
	else
	{
		Animation.StartFrame = 0;
	}

	if (_End != -1)
	{
		Animation.EndFrame = _End;
	}
	else
	{
		Animation.EndFrame = Animation.Sprite->GetSpriteCount() - 1;
	}

	Animation.Inters.resize(abs(static_cast<int>(Animation.EndFrame - Animation.StartFrame)) + 1);
	Animation.Frames.resize(abs(static_cast<int>(Animation.EndFrame - Animation.StartFrame)) + 1);

	int FrameDir = 1;
	if (_Start > _End)
	{
		FrameDir = -1;
	}

	size_t Start = Animation.StartFrame;

	for (size_t i = 0; i < Animation.Inters.size(); i++)
	{
		Animation.Frames[i] = Start;
		Animation.Inters[i] = _Inter;
		Start += FrameDir;
	}
	Animation.Loop = _Loop;
}

void GameEngineRenderer::ChangeAnimation(const std::string& _AnimationName, bool _ForceChange /*= false*/)
{
	Animation* ChangeAnimation = FindAnimation(_AnimationName);
	if (nullptr == ChangeAnimation)
	{
		MsgBoxAssert(_AnimationName + "존재하지 않는 애니메이션으로 교환하려고 했습니다.");
		return;
	}

	if (ChangeAnimation == CurAnimation && false == _ForceChange)
	{
		return;
	}

	CurAnimation = ChangeAnimation;
	CurAnimation->CurInter = CurAnimation->Inters[0];
	CurAnimation->CurFrame = 0;
}

void GameEngineRenderer::Start()
{
	Camera = GetActor()->GetLevel()->GetMainCamera();
}

void GameEngineRenderer::SetOrder(int _Order)
{
	if (nullptr == Camera)
	{
		MsgBoxAssert("카메라가 세팅되어있지 않습니다.");
	}
	std::list<GameEngineRenderer*>& PrevRenders = Camera->Renderers[GetOrder()];
	PrevRenders.remove(this);

	GameEngineObject::SetOrder(_Order);
	std::list<GameEngineRenderer*>& NextRenders = Camera->Renderers[GetOrder()];
	NextRenders.push_back(this);
}
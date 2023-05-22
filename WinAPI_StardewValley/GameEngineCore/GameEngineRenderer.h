#pragma once
#include <string>
#include <map>
#include <vector>

#include <GameEngineBase/GameEngineMath.h>

#include <GameEngineCore/GameEngineObject.h>

class GameEngineWindowTexture;
class GameEngineActor;
class GameEngineCamera;
class GameEngineSprite;
class GameEngineRenderer : public GameEngineObject
{
	friend GameEngineCamera;
	friend GameEngineActor;
public:
	// constructer destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete function
	GameEngineRenderer(const GameEngineRenderer& _Ohter) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Ohter) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetTexture(const std::string& _Name);

	void SetSprite(const std::string& _Name, size_t _Index = 0);

	void SetRenderPos(const float4& _Pos)
	{
		RenderPos = _Pos;
	}

	void SetRenderScale(const float4& _Scale)
	{
		RenderScale = _Scale;
		ScaleCheck = true;
	}

	void SetCopyPos(const float4& _Pos)
	{
		CopyPos = _Pos;
	}

	void SetCopyScale(const float4& _Scale)
	{
		CopyScale = _Scale;
	}

	void SetScaleRatio(const float _Ratio)
	{
		ScaleRatio = _Ratio;
	}

	void SetRenderScaleToTexture();

	bool IsDeath() override;

protected:

private:
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineActor* Master = nullptr;
	GameEngineSprite* Sprite = nullptr;
	bool ScaleCheck = false;
	float ScaleRatio = 1.0f;

	float4 RenderPos = {};
	float4 RenderScale = {};

	float4 CopyPos = {};
	float4 CopyScale = {};
	void Render(GameEngineCamera* _Camera, float _DeltaTime);

private:
	class Animation
	{
	public:
		GameEngineSprite* Sprite = nullptr;
		size_t CurFrame = 0;
		size_t StartFrame = -1;
		size_t EndFrame = -1;
		float CurInter = 0.0f;
		std::vector<size_t> Frames;
		std::vector<float> Inters;
		bool Loop = true;
	};

public:
	Animation* FindAnimation(const std::string& _AnimationName);

	void CreateAnimation(
		const std::string& _AnimationName,
		const std::string& _SpriteName,
		size_t _Start = -1, size_t _End = -1,
		float _Inter = 0.1f,
		bool _Loop = true);

	void ChangeAnimation(const std::string& _AnimationName, bool _ForceChange = false);
	
	std::map<std::string, Animation> AllAnimation;
	Animation* CurAnimation = nullptr;
};


#pragma once
#include <string>

#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineObject.h>
class GameEngineCamera;
class GameEngineActor;
class GameEngineWindowTexture;
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

	void SetRenderScaleToTexture();

	bool IsDeath() override;
protected:

private:
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineActor* Master = nullptr;
	bool ScaleCheck = false;

	float4 RenderPos = {};
	float4 RenderScale = {};

	float4 CopyPos = {};
	float4 CopyScale = {};
	void Render(GameEngineCamera* _Camera);
};


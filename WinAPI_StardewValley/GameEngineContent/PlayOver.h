#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineWindowTexture;
class GameEngineRenderer;
class PlayOver : public GameEngineActor
{
public:
	// constructer destructer
	PlayOver();
	~PlayOver();

	// delete function
	PlayOver(const PlayOver& _Ohter) = delete;
	PlayOver(PlayOver&& _Ohter) noexcept = delete;
	PlayOver& operator=(const PlayOver& _Other) = delete;
	PlayOver& operator=(PlayOver&& _Other) noexcept = delete;

	GameEngineRenderer* Renderer = nullptr;
	GameEngineCollision* Collision = nullptr;

	void Init(const std::string& _FileName);

	float4 GetScale()
	{
		return Scale;
	}

	void SetRenderScale(float4 _RenderScale)
	{
		RenderScale = _RenderScale;
	}

	float4 GetRenderScale()
	{
		return RenderScale;
	}

	std::string GetFileName()
	{
		return FileName;
	}

protected:

private:
	std::string FileName = "";
	float4 Scale = float4::ZERO;
	float4 RenderScale = float4::ZERO;

	void Start() override;
	void Update(float _Delta) override;
};


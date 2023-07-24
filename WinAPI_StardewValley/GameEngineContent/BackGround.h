#pragma once
#include <GameEngineBase/GameEngineMath.h>

#include <GameEngineCore/GameEngineActor.h>

class GameEngineWindowTexture;
class BackGround : public GameEngineActor
{
public:

	// constructer destructer
	BackGround();
	~BackGround();

	// delete function
	BackGround(const BackGround& _Ohter) = delete;
	BackGround(BackGround&& _Ohter) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	void Init(const std::string& _FileName, float _RenderScaleRatio = 1.0f);
	void Init(const std::string& _FileName, const std::string& _CollisionFileName, float _RenderScaleRatio = 1.0f);
	
	const float4 GetScale()
	{
		return Scale;
	}

	const float4 GetRenderScale()
	{
		return RenderScale;
	}

	GameEngineRenderer* GetRenderer()
	{
		return Renderer;
	}

	void SwitchBackGroundRender();

	void ResetBackGroundRender();

protected:

private:
	GameEngineRenderer* Renderer = nullptr;
	GameEngineRenderer* CollisionRenderer = nullptr;
	GameEngineWindowTexture* CollisionTexture = nullptr;

	bool BackGroundTexture = true;

	float4 Scale = float4::ZERO;
	float4 RenderScale = float4::ZERO;

	void Start() override;
	void Update(float _Delta) override;
};


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

	void Init(const std::string& _FileName);
	void Init(const std::string& _FileName, const std::string& _CollisionFileName);
	
	const float4 GetScale()
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

	void SwitchBackGroundRender();

	void ResetBackGroundRender();

	GameEngineRenderer* Renderer = nullptr;
	GameEngineRenderer* CollisionRenderer = nullptr;
protected:

private:
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineWindowTexture* CollisionTexture = nullptr;

	bool BackGroundTexture = true;

	std::string FileName = "";
	float4 Scale = float4::ZERO;
	float4 RenderScale = float4::ZERO;

	void Start() override;
	void Update(float _Delta) override;
};


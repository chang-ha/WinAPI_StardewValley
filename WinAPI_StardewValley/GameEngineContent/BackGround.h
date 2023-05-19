#pragma once
#include <GameEngineBase/GameEngineMath.h>

#include <GameEngineCore/GameEngineActor.h>

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
	GameEngineRenderer* Renderer;
	
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
protected:

private:
	std::string FileName = "";
	float4 Scale;
	float4 RenderScale;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};


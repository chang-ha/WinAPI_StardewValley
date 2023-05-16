#pragma once
#include <GameEngineBase/GameEngineMath.h>

#include <GameEngineCore/GameEngineActor.h>

class BackGround : public GameEngineActor
{
public:
	static BackGround MainBackGround;

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

	float4 GetScale()
	{
		return Scale;
	}
protected:

private:
	std::string FileName = "";

	float4 Scale;
	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};


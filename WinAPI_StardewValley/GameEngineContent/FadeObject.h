#pragma once
#include <GameEngineCore/GameEngineActor.h>

class FadeObject : public GameEngineActor
{
public:
	// constructer destructer
	FadeObject();
	~FadeObject();

	// delete function
	FadeObject(const FadeObject& _Ohter) = delete;
	FadeObject(FadeObject&& _Ohter) noexcept = delete;
	FadeObject& operator=(const FadeObject& _Other) = delete;
	FadeObject& operator=(FadeObject&& _Other) noexcept = delete;

	/// <summary>
	/// bool _Black = false == Fade_White
	/// bool _Black = true == Fade_Dark
	/// </summary>
	/// <param name="_Black"></param>
	void Init(bool _Black = true, float _FadeUpSpeed = 400.0f);

	void Update(float _Delta) override;

	void FadeIn(float _Delta);

	void FadeOut(float _Delta);

	void FadeDeath();

	void FadeInOn()
	{
		CurAlpha = 255;
		FadeInValue = true;
	}

	void FadeOutOn()
	{
		CurAlpha = 0;
		FadeOutValue = true;
	}

	bool IsFadeEnd()
	{
		return FadeEnd;
	}
protected:

private:
	bool FadeEnd = false;
	bool FadeDeathValue = false;
	bool FadeInValue = false;
	bool FadeOutValue = false;
	int CurAlpha = 0;
	float FadeSpeed = 0;
	float FadeUpSpeed = 0;
	float DeathTime = 0.5f;
	GameEngineRenderer* Renderer = nullptr;

	void Start() override;
};


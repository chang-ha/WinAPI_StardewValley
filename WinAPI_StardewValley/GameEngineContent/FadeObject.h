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
	void Init(bool _Black = true);

	void Update(float _Delta) override;

	void FadeIn(float _Delta);

	void FadeOut(float _Delta);

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
	bool FadeInValue = false;
	bool FadeOutValue = false;
	float FadeSpeed = 0;
	int CurAlpha = 0;
	GameEngineRenderer* Renderer = nullptr;

	void Start() override;
};


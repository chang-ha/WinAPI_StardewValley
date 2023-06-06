#pragma once
#include <GameEnginePlatform/GameEngineSound.h>

#include <GameEngineCore/GameEngineActor.h>

class ShippingBin : public GameEngineActor
{
public:
	// constructer destructer
	ShippingBin();
	~ShippingBin();

	// delete function
	ShippingBin(const ShippingBin& _Ohter) = delete;
	ShippingBin(ShippingBin&& _Ohter) noexcept = delete;
	ShippingBin& operator=(const ShippingBin& _Other) = delete;
	ShippingBin& operator=(ShippingBin&& _Other) noexcept = delete;

	GameEngineRenderer* BodyRenderer = nullptr;
	GameEngineRenderer* CaseRenderer = nullptr;
	GameEngineCollision* Collision = nullptr;
protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	bool IsOpen = false;

	GameEngineSoundPlayer EffectPlayer;
};


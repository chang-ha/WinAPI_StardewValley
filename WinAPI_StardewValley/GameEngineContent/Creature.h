#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineWindowTexture;
class Creature : public GameEngineActor
{
public:
	// constructer destructer
	Creature();
	~Creature();

	// delete function
	Creature(const Creature& _Ohter) = delete;
	Creature(Creature&& _Ohter) noexcept = delete;
	Creature& operator=(const Creature& _Other) = delete;
	Creature& operator=(Creature&& _Other) noexcept = delete;

	void Init(const std::string& _FileName);

	GameEngineRenderer* Renderer = nullptr;
protected:

private:
	GameEngineWindowTexture* Texture = nullptr;

	std::string FileName = "";
	float4 Scale = float4::ZERO;

	void Start() override;
	void Update(float _Delta) override;
};


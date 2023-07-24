#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineWindowTexture;
class GameEngineCollision;
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

	GameEngineRenderer* GetRenderer()
	{
		return Renderer;
	}
protected:

private:
	GameEngineRenderer* Renderer = nullptr;
	GameEngineWindowTexture* Texture = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};


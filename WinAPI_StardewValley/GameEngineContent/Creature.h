#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};


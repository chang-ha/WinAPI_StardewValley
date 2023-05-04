#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Title : public GameEngineActor
{
public:
	// constructer destructer
	Title();
	~Title();

	// delete function
	Title(const Title& _Ohter) = delete;
	Title(Title&& _Ohter) noexcept = delete;
	Title& operator=(const Title& _Other) = delete;
	Title& operator=(Title&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};


#pragma once
#include <GameEngineCore/GameEngineActor.h>

class TitleBird : public GameEngineActor
{
public:
	// constructer destructer
	TitleBird();
	~TitleBird();

	// delete function
	TitleBird(const TitleBird& _Ohter) = delete;
	TitleBird(TitleBird&& _Ohter) noexcept = delete;
	TitleBird& operator=(const TitleBird& _Other) = delete;
	TitleBird& operator=(TitleBird&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};


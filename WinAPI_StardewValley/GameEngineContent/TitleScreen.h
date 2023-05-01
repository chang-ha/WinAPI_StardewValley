#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class TitleScreen : public GameEngineLevel
{
public:
	// constructer destructer
	TitleScreen();
	~TitleScreen();

	// delete function
	TitleScreen(const TitleScreen& _Ohter) = delete;
	TitleScreen(TitleScreen&& _Ohter) noexcept = delete;
	TitleScreen& operator=(const TitleScreen& _Other) = delete;
	TitleScreen& operator=(TitleScreen&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	void Render() override;
	void Release() override;
};


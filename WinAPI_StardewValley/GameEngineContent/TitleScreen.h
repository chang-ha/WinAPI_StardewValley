#pragma once
#include "ContentLevel.h"

class PlayOver;
class TitleScreen : public ContentLevel
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
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render() override;
	void Release() override;

	PlayOver* Logo = nullptr;
	PlayOver* New_Button = nullptr;
	PlayOver* Load_Button = nullptr;
	PlayOver* Coop_Button = nullptr;
	PlayOver* Exit_Button = nullptr;
};


#pragma once
#include "ContentLevel.h"

class Creature;
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
	float4 Speed = {};
	bool IsSkip = false;
	bool IsMouseOn = false;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Release() override;

	Creature* Bird1 = nullptr;
	Creature* Bird2 = nullptr;
	// Creature* LargeCloud1 = nullptr;
	// Creature* LargeCloud2 = nullptr;

	PlayOver* LeftTree = nullptr;
	PlayOver* RightTree = nullptr;
	PlayOver* LeftLeaf = nullptr;
	PlayOver* RightLeaf = nullptr;

	PlayOver* Logo = nullptr;
	PlayOver* New_Button = nullptr;
	PlayOver* Load_Button = nullptr;
	PlayOver* Coop_Button = nullptr;
	PlayOver* Exit_Button = nullptr;
};


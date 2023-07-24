#pragma once
#include "ContentLevel.h"

class ContentActor;
class PlayOver;
class EndingActor;
class EndingLevel : public ContentLevel
{
public:
	// constructer destructer
	EndingLevel();
	~EndingLevel();

	// delete function
	EndingLevel(const EndingLevel& _Ohter) = delete;
	EndingLevel(EndingLevel&& _Ohter) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;

protected:

private:
	bool RValueBool = true;
	unsigned char RValue = 0b11111111;
	bool GValueBool = false;
	unsigned char GValue = 0b00000000;
	bool BValueBool = false;
	unsigned char BValue = 0b00000000;

	// UI
	GameEngineWindowTexture* Texture = nullptr;
	BackGround* BackBelow = nullptr;
	PlayOver* CategoryActor = nullptr;
	GameEngineCollision* SkipButtonCollision = nullptr;

	// Actor
	EndingActor* Dog = nullptr;
	EndingActor* Cat = nullptr;

	void ColorValueUpdate(unsigned char& _RGBValue, bool _BoolValue);
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
};


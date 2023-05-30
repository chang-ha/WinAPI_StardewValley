#define RENDERRATIO 4

#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

class BackGround;
class Player;
class ContentUIManager;
class ContentLevel : public GameEngineLevel
{
public:
	// constructer destructer
	ContentLevel();
	~ContentLevel();

	// delete function
	ContentLevel(const ContentLevel& _Ohter) = delete;
	ContentLevel(ContentLevel&& _Ohter) noexcept = delete;
	ContentLevel& operator=(const ContentLevel& _Other) = delete;
	ContentLevel& operator=(ContentLevel&& _Other) noexcept = delete;

	float4 GetRenderScale();

	ContentUIManager* UIManager = nullptr;
	GameEngineSoundPlayer BGMPlayer;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	BackGround* Back = nullptr;
	Player* Farmer = nullptr;
private:

};


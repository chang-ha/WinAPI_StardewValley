#pragma once
#include <string>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "ContentMouse.h"
#include "GlobalValue.h"

class BackGround;
class Player;
class ContentUIManager;
class TileMap;
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
	GameEngineSoundPlayer EffectPlayer;

	ContentMouse* GetMainMouse()
	{
		return MainMouse;
	}

	std::string GetPrevLevel()
	{
		return PrevLevel;
	}

	std::string GetNextLevel()
	{
		return NextLevel;
	}
protected:
	float4 WinScale = {};

	BackGround* Back = nullptr;
	Player* Farmer = nullptr;
	ContentMouse* MainMouse = nullptr;
	TileMap* UITileMap = nullptr;
	float4 CurIndex = {};
	float4 PrevIndex = {};

	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	std::string PrevLevel = "";
	std::string NextLevel = "";
private:
};


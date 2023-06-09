#pragma once
#include <string>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "ContentMouse.h"
#include "GlobalValue.h"

class BackGround;
class TileMap;
class FadeObject;
class ContentLevel : public GameEngineLevel
{
public:
	// constructer destructer
	ContentLevel();
	~ContentLevel() override;

	// delete function
	ContentLevel(const ContentLevel& _Ohter) = delete;
	ContentLevel(ContentLevel&& _Ohter) noexcept = delete;
	ContentLevel& operator=(const ContentLevel& _Other) = delete;
	ContentLevel& operator=(ContentLevel&& _Other) noexcept = delete;

	float4 GetRenderScale();

	GameEngineSoundPlayer BGMPlayer;
	GameEngineSoundPlayer EffectPlayer;

	std::string GetPrevLevel()
	{
		return PrevLevel;
	}

	std::string GetNextLevel()
	{
		return NextLevel;
	}

	std::string GetBuildingLevel()
	{
		return Building;
	}

	TileMap* GetUITileMap()
	{
		return UITileMap;
	}

	FadeObject* GetFadeObject()
	{
		return _CurFade;
	}

	void SetFadeObject(FadeObject* _Object)
	{
		_CurFade = _Object;
	}
	
protected:
	float4 CurIndex = {};
	float4 PrevIndex = {};
	BackGround* Back = nullptr;
	TileMap* UITileMap = nullptr;
	FadeObject* _CurFade = nullptr;

	std::string PrevLevel = "";
	std::string NextLevel = "";
	std::string Building = "";

	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
};


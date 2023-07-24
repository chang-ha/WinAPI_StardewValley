#pragma once
#include "ContentLevel.h"

class Player;
class TileMap;
class ContentCrops;
class Farm : public ContentLevel
{
public:
	// constructer destructer
	Farm();
	~Farm();

	// delete function
	Farm(const Farm& _Ohter) = delete;
	Farm(Farm&& _Ohter) noexcept = delete;
	Farm& operator=(const Farm& _Other) = delete;
	Farm& operator=(Farm&& _Other) noexcept = delete;

	TileMap* GetTileMap()
	{
		return FarmTileMap;
	}

	TileMap* GetWateringTileMap()
	{
		return FarmWateringTileMap;
	}

	void GroundHoe();
	void GroundWatering();
	void GroundSeeding(ContentItem* _SeedItem);

protected:

private:
	TileMap* FarmTileMap = nullptr;
	TileMap* FarmWateringTileMap = nullptr;
	std::list<ContentCrops*> AllCrops;

	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void TileSetting(const int _X, const int _Y);
	void WateringTileSetting(const int _X, const int _Y);
};


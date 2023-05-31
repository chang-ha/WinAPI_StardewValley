#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <string>
#include <vector>
#include "GameEngineActor.h"

// Ό³Έν :
class GameEngineSprite;
class TileMap : public GameEngineActor
{
public:
	// constructer destructer
	TileMap();
	~TileMap();

	// delete function
	TileMap(const TileMap& _Ohter) = delete;
	TileMap(TileMap&& _Ohter) noexcept = delete;
	TileMap& operator=(const TileMap& _Other) = delete;
	TileMap& operator=(TileMap&& _Other) noexcept = delete;

	void Update(float _DeltaTime) override;

	bool IsOver(int _X, int _Y);

	float4 IndexToPos(int _X, int _Y);

	float4 PosToIndex(float4 _Pos);

	void CreateTileMap(const std::string& _Sprite, int _X, int _Y, float4 _TileSize, int _Order);

	GameEngineRenderer* GetTile(int _X, int _Y);
		
	void SetTile(int X, int Y, int _Index, float4 _TilePos = float4::ZERO, bool _IsImageSize = false);

	void SetTile(float4 _Pos, int _Index, float4 _TilePos = float4::ZERO, bool _IsImageSize = false);

protected:

private:
	int TileX = 0;
	int TileY = 0;
	int Order = 0;
	float4 TileSize = {};
	std::string Sprite = "";
	std::vector<std::vector<class GameEngineRenderer*>> Tiles;
};


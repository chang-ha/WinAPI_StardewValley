﻿#include "TileMap.h"
#include "GameEngineRenderer.h"

TileMap::TileMap()
{

}

TileMap::~TileMap()
{

}

void TileMap::Update(float _DeltaTime)
{
	SetPos(float4::ZERO);
}

bool TileMap::IsOver(int _X, int _Y)
{
	if (_X < 0)
	{
		return true;
	}

	if (_Y < 0)
	{
		return true;
	}

	if (TileX <= _X)
	{
		return true;
	}

	if (TileY <= _Y)
	{
		return true;
	}

	return false;
}

float4 TileMap::IndexToPos(int _X, int _Y)
{
	return { TileSize.X * _X, TileSize.Y * _Y };
}

float4 TileMap::PosToIndex(float4 _Pos)
{
	return { _Pos.X / TileSize.X , _Pos.Y / TileSize.Y };
}

void TileMap::CreateTileMap(const std::string& _Sprite, int _X, int _Y, float4 _TileSize, int _Order)
{
	Sprite = _Sprite;
	TileX = _X;
	TileY = _Y;
	TileSize = _TileSize;

	Tiles.resize(_Y);
	for (int y = 0; y < _Y; y++)
	{
		Tiles[y].resize(_X);
	}

}

GameEngineRenderer* TileMap::GetTile(int _X, int _Y)
{
	if (true == IsOver(_X, _Y))
	{
		return nullptr;
	}

	return Tiles[_Y][_X];
}

void TileMap::SetTile(float4 _Pos, int _Index, float4 _TilePos /*= float4::ZERO*/, bool _IsImageSize /*= false*/)
{
	float4 Index = PosToIndex(_Pos);

	SetTile(Index.iX(), Index.iY(), _Index, _TilePos, _IsImageSize/* = false*/);
}

void TileMap::SetTile(int X, int Y, int _Index, float4 _TilePos, bool _IsImageSize/* = false*/)
{
	if (true == IsOver(X, Y))
	{
		return;
	}

	if (nullptr == Tiles[Y][X])
	{
		Tiles[Y][X] = CreateRenderer(Order);
	}

	Tiles[Y][X]->SetSprite(Sprite, _Index);
	Tiles[Y][X]->SetRenderPos(IndexToPos(X, Y) + TileSize.Half() + _TilePos);

	if (false == _IsImageSize)
	{
		Tiles[Y][X]->SetRenderScale(TileSize);
	}
	else {
		Tiles[Y][X]->SetRenderScaleToTexture();
	}
}
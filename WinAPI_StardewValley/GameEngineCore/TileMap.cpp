#include "TileMap.h"
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

	if (nullptr == LerpTileRenderer)
	{
		return;
	}

	LerpTime += _DeltaTime * LerpSpeed;
	float4 Pos = float4::LerpClimp(StartPos, EndPos, LerpTime);
	LerpTileRenderer->SetRenderPos(Pos);

	if (1 <= LerpTime)
	{
		float4 Pos = PosToIndex(EndPos - TileSize.Half() - LerpTilePos);

		Tiles[Pos.iY()][Pos.iX()] = LerpTileRenderer;

		LerpTileRenderer = nullptr;
	}
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
	Order = _Order;

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

bool TileMap::MoveTile(int X1, int Y1, int X2, int Y2, float4 _TilePos)
{
	if (nullptr == Tiles[Y1][X1])
	{
		return false;
	}

	if (nullptr != Tiles[Y2][X2])
	{
		return false;
	}

	GameEngineRenderer* Tile = Tiles[Y1][X1];
	Tiles[Y1][X1] = nullptr;

	Tiles[Y2][X2] = Tile;
	Tile->SetRenderPos(IndexToPos(X2, Y2) + TileSize.Half() + _TilePos);
	return true;
}

GameEngineRenderer* TileMap::SetTile(float4 _Pos, int _Index, float4 _TilePos /*= float4::ZERO*/, bool _IsImageSize /*= false*/)
{
	float4 Index = PosToIndex(_Pos);

	return SetTile(Index.iX(), Index.iY(), _Index, _TilePos, _IsImageSize/* = false*/);
}

GameEngineRenderer* TileMap::SetTile(int X, int Y, int _Index, float4 _TilePos, bool _IsImageSize/* = false*/)
{
	if (true == IsOver(X, Y))
	{
		return nullptr;
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
	else
	{
		Tiles[Y][X]->SetRenderScaleToTexture();
	}
	return Tiles[Y][X];
}

void TileMap::DeathTile(float4 _Pos)
{
	float4 Index = PosToIndex(_Pos);

	DeathTile(Index.iX(), Index.iY());
}

void TileMap::DeathTile(int X, int Y)
{
	if (true == IsOver(X, Y))
	{
		return;
	}

	if (nullptr == Tiles[Y][X])
	{
		return;
	}

	Tiles[Y][X]->Death();
	Tiles[Y][X] = nullptr;

}

bool TileMap::LerpTile(int X1, int Y1, int X2, int Y2, float4 _TilePos)
{
	if (nullptr != LerpTileRenderer)
	{
		return false;
	}

	if (nullptr == Tiles[Y1][X1])
	{
		return false;
	}

	if (nullptr != Tiles[Y2][X2])
	{
		return false;
	}

	LerpTileRenderer = Tiles[Y1][X1];
	Tiles[Y1][X1] = nullptr;
	Tiles[Y2][X2] = nullptr;
	LerpTilePos = _TilePos;

	StartPos = IndexToPos(X1, Y1) + TileSize.Half() + _TilePos;
	EndPos = IndexToPos(X2, Y2) + TileSize.Half() + _TilePos;
	LerpTime = 0.0f;

	return true;
}
#pragma once

class GameEngineTexture
{
public:
	// constructer destructer
	GameEngineTexture();
	~GameEngineTexture();

	// delete function
	GameEngineTexture(const GameEngineTexture& _Ohter) = delete;
	GameEngineTexture(GameEngineTexture&& _Ohter) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

protected:

private:

};


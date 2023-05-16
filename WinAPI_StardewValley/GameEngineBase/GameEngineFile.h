#pragma once
#include <string>

#include "GameEnginePath.h"

class GameEngineFile : public GameEnginePath
{
public:
	// constructer destructer
	GameEngineFile();
	GameEngineFile(const std::string& _Path);
	~GameEngineFile();

	// // delete function
	// GameEngineFile(const GameEngineFile& _Ohter) = delete;
	// GameEngineFile(GameEngineFile&& _Ohter) noexcept = delete;
	// GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	// GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;

protected:

private:

};


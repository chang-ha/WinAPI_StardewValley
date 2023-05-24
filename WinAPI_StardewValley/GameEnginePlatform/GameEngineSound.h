#pragma once
#include <string>

class GameEngineSound
{
public:
	// constructer destructer
	GameEngineSound();
	~GameEngineSound();

	// delete function
	GameEngineSound(const GameEngineSound& _Ohter) = delete;
	GameEngineSound(GameEngineSound&& _Ohter) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

	static void SoundLoad(std::string& _Name, std::string& _Path);
	static void SoundPlay(std::string& _Name);
	static void PlayBgm(std::string& _Name);
	static void StopBgm();

protected:

private:

};


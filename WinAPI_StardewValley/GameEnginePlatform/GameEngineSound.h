#pragma once
#include <string>

#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>

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

	static void Init();
	static void SoundLoad(const std::string& _Name, const std::string& _Path);
	static void SoundPlay(const std::string& _Name);
	static void PlayBgm(const std::string& _Name);
	static void StopBgm();

protected:

private:

};


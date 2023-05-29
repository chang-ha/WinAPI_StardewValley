#pragma once
#include <string>
#include <map>
#include <GameEnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>

#include <GameEngineBase/GameEnginePath.h>

class GameEngineSound;
class GameEngineSoundPlayer
{
	friend GameEngineSound;
public:
	void SetVolume(float _Volume);
	void Stop();

	GameEngineSoundPlayer()
	{

	}
private:
	GameEngineSoundPlayer(FMOD::Channel* _Control)
		: Control(_Control)
	{
	}

	FMOD::Channel* Control = nullptr;
};

class GameEngineSound
{
	friend GameEngineSoundPlayer;
public:
	// constructer destructer
	GameEngineSound();
	~GameEngineSound();

	// delete function
	GameEngineSound(const GameEngineSound& _Ohter) = delete;
	GameEngineSound(GameEngineSound&& _Ohter) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

	static GameEngineSound* FindSound(const std::string& _Name);

	static void SoundLoad(const std::string& _Name, const std::string& _Path);
	static void SoundLoad(const std::string& _Path)
	{
		GameEnginePath Path = _Path;
		SoundLoad(Path.GetFileName(), _Path);
	}

	static GameEngineSoundPlayer SoundPlay(const std::string& _Name);

	static void SetGlobalVolume(float _Value)
	{
		GlobalVolume = _Value;
	}

	static float GetGlobalVolume()
	{
		return GlobalVolume;
	}

	static void Update();
	static void Release();

protected:

private:
	static std::map<std::string, GameEngineSound*> AllSound;
	static float GlobalVolume;

	FMOD::Sound* SoundHandle = nullptr;
	FMOD::Channel* Play();
	void Load(const std::string& _Path);
};


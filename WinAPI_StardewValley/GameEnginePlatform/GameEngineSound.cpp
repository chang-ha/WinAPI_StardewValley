#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>

#include "GameEngineSound.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif 

// Sound Player 
void GameEngineSoundPlayer::SetVolume(float _Volume)
{
	Control->setVolume(_Volume * GameEngineSound::GlobalVolume);
}

void GameEngineSoundPlayer::Stop()
{
	Control->stop();
}

// FMOD 사용을 위한 핸들
FMOD::System* SoundSystem = nullptr;
float GameEngineSound::GlobalVolume = 1.0f;

class SoundSystemCreator
{
public:
	SoundSystemCreator()
	{
		if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
		{
			MsgBoxAssert("사운드 시스템 생성에 실패했습니다.");
		}

		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgBoxAssert("사운스 시스템 Init에 실패했습니다.");
		}
	}

	~SoundSystemCreator()
	{
		SoundSystem->release();
	}
};

SoundSystemCreator SoundInitObject = SoundSystemCreator();

std::map<std::string, GameEngineSound*> GameEngineSound::AllSound;

GameEngineSound::GameEngineSound()
{

}

GameEngineSound::~GameEngineSound()
{
	if (nullptr != SoundHandle)
	{
		SoundHandle->release();
	}
}

void GameEngineSound::Update()
{
	if (nullptr == SoundSystem)
	{
		MsgBoxAssert("Sound System이 생성되지 않아서 사운드 업데이트를 돌릴수가 없습니다.");
	}
	SoundSystem->update();
}

void GameEngineSound::Release()
{
	for (std::pair<std::string, GameEngineSound*> Pair : GameEngineSound::AllSound)
	{
		if (nullptr == Pair.second)
		{
			return;
		}

		delete Pair.second;
	}
}

GameEngineSound* GameEngineSound::FindSound(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	std::map<std::string, GameEngineSound*>::iterator FindIter = AllSound.find(UpperName);
	if (AllSound.end() == FindIter)
	{
		return nullptr;
	}
	return FindIter->second;
}

void GameEngineSound::SoundLoad(const std::string& _Name, const std::string& _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	GameEngineSound* NewSound = new GameEngineSound();
	NewSound->Load(_Path);
	AllSound.insert(std::make_pair(UpperName, NewSound));
}

GameEngineSoundPlayer GameEngineSound::SoundPlay(const std::string& _Name)
{
	GameEngineSound* Sound = FindSound(_Name);
	if (nullptr == Sound)
	{
		MsgBoxAssert(_Name + "사운드가 존재하지 않습니다.");
		return nullptr;
	}
	GameEngineSoundPlayer SoundPlayer = Sound->Play();
	SoundPlayer.SetVolume(1.0f);
	return SoundPlayer;
}

void GameEngineSound::Load(const std::string& _Path)
{
	std::string UTF8 = GameEngineString::AnsiToUTF8(_Path);
	SoundSystem->createSound(UTF8.c_str(), FMOD_LOOP_NORMAL, nullptr, &SoundHandle);
	if (nullptr == SoundHandle)
	{
		MsgBoxAssert("사운드로드에 실패했습니다.");
	}
}

FMOD::Channel* GameEngineSound::Play()
{
	FMOD::Channel* SoundControl = nullptr;

	SoundSystem->playSound(SoundHandle, nullptr, false, &SoundControl);

	return SoundControl;
}
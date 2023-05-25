#include <GameEngineBase/GameEngineDebug.h>

#include "GameEngineSound.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "..\\GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif 

// FMOD 사용을 위한 핸들
FMOD::System* SoundSystem = nullptr;

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

GameEngineSound::GameEngineSound()
{

}

GameEngineSound::~GameEngineSound()
{

}

void GameEngineSound::Init()
{

}

void GameEngineSound::SoundLoad(const std::string& _Name, const std::string& _Path)
{

}

void GameEngineSound::SoundPlay(const std::string& _Name)
{

}

void GameEngineSound::PlayBgm(const std::string& _Name)
{

}

void GameEngineSound::StopBgm()
{

}
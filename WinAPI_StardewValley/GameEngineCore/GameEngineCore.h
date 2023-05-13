#pragma once
#include <string>
#include <map>
#include <Windows.h>

#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

#include "GameEngineObject.h"

class CoreProcess : public GameEngineObject
{
};

class GameEngineLevel;
class GameEngineCore
{
public:
	// delete function
	GameEngineCore(const GameEngineCore& _Ohter) = delete;
	GameEngineCore(GameEngineCore&& _Ohter) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	template <typename CoreProcessType>
	static void EngineStart(const std::string& _Title, HINSTANCE _Inst)
	{
		EngineStart(_Title, _Inst, new CoreProcessType());
	}

	template<typename LevelType>
	static void CreateLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		if (AllLevel.end() != AllLevel.find(Upper))
		{
			MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel이 이미 존재합니다.");
			return;
		}
		GameEngineLevel* NewLevel = new LevelType();
		LevelInit(NewLevel);
		AllLevel.insert(std::make_pair(Upper, NewLevel));
	}

	static void ChangeLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel.find(Upper);
		if (AllLevel.end() == FindIter)
		{
			MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel이 존재하지 않습니다.");
			return;
		}
		NextLevel = FindIter->second;
	}

protected:

private:
	static std::string WindowTitle;
	static CoreProcess* Process;

	static std::map<std::string, GameEngineLevel*> AllLevel;
	static GameEngineLevel* CurLevel;
	static GameEngineLevel* NextLevel;

	static void EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr);
	static void CoreStart(HINSTANCE _Inst);
	static void CoreUpdate();
	static void CoreEnd();
	static void LevelInit(GameEngineLevel* _Level);

	// constructer destructer
	GameEngineCore();
	~GameEngineCore();
};


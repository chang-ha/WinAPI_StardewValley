#pragma once
#include <GameEngineBase/GameEngineDebug.h>
#include <Windows.h>
#include <map>
#include <GameEngineBase/GameEngineString.h>

class GameEngineLevel;
class GameEngineCore
{
public:
	// constructer destructer
	GameEngineCore();
	~GameEngineCore();

	// delete function
	GameEngineCore(const GameEngineCore& _Ohter) = delete;
	GameEngineCore(GameEngineCore&& _Ohter) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	static void EngineStart(const std::string& _Title, HINSTANCE _Inst);

	template<typename Leveltype>
	static void CreateLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		if (AllLevel.end() != AllLevel.find(Upper))
		{
			MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel이 이미 존재합니다.");
			return;
		}
		GameEngineLevel* NewLevel = new Leveltype();
		AllLevel.insert(std::make_pair(Upper, NewLevel));
	}
protected:

private:
	static std::string WindowTitle;
	
	static void CoreStart(HINSTANCE _Inst);
	static void CoreUpdate();
	static void CoreEnd();
	static std::map<std::string, GameEngineLevel*> AllLevel;
};


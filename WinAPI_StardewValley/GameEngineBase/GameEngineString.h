#pragma once
#include <string>

class GameEngineString
{
public:
	// constructer destructer
	GameEngineString();
	~GameEngineString();

	// delete function
	GameEngineString(const GameEngineString& _Ohter) = delete;
	GameEngineString(GameEngineString&& _Ohter) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;

	static std::string ToUpperReturn(const std::string& _Value)
	{
		std::string UpperString = _Value;
		for (size_t i = 0; i < UpperString.size(); i++)
		{
			UpperString[i] = toupper(UpperString[i]);
		}
		return UpperString;
	}
protected:

private:

};


#include <Windows.h>

#include "GameEngineString.h"
#include "GameEngineDebug.h"

GameEngineString::GameEngineString()
{

}

GameEngineString::~GameEngineString()
{

}


std::wstring GameEngineString::AnsiToUnicode(const std::string& _Text)
{
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("멀티바이트문자열을 와이드바이트문자열로 변환할 수 없습니다.");
		return L"";
	}
	std::wstring Result;
	Result.resize(Size);
	Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Result[0], Size);
	if (0 == Size)
	{
		MsgBoxAssert("멀티바이트문자열을 와이드바이트문자열로 변환할 수 없습니다.");
		return L"";
	}
	return Result;
}

std::string GameEngineString::UnicodeToAnsi(const std::wstring& _Text)
{
	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("와이드바이트문자열을 멀티바이트문자열로 변환할 수 없습니다.");
		return "";
	}
	std::string Result;
	Result.resize(Size);
	Size = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);
	if (0 == Size)
	{
		MsgBoxAssert("와이드바이트문자열을 멀티바이트문자열로 변환할 수 없습니다.");
		return "";
	}
	return Result;
}

std::string GameEngineString::UnicodeToUTF8(const std::wstring& _Text)
{
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("와이드바이트문자열을 멀티바이트문자열로 변환할 수 없습니다.");
		return "";
	}
	std::string Result;
	Result.resize(Size);
	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);
	if (0 == Size)
	{
		MsgBoxAssert("와이드바이트문자열을 멀티바이트문자열로 변환할 수 없습니다.");
		return "";
	}
	return Result;
}

std::string GameEngineString::AnsiToUTF8(const std::string& _Text)
{
	std::wstring UniCode = AnsiToUnicode(_Text);
	return UnicodeToUTF8(UniCode);
}

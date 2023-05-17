#pragma once
#include <string>
#include <filesystem>

class GameEnginePath
{
public:
	// constructer destructer
	GameEnginePath();
	GameEnginePath(const std::string& _Path);
	~GameEnginePath();

	// // delete function
	// GameEnginePath(const GameEnginePath& _Ohter) = delete;
	// GameEnginePath(GameEnginePath&& _Ohter) noexcept = delete;
	// GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	// GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	void SetCurrentPath();
	void MoveParent();
	void MoveParentToExistsChild(const std::string& _ChildPath);
	void MoveChild(const std::string& _ChildPath);
	
	std::string PlusFilePath(const std::string& _ChildPath);
	std::string GetStringPath()
	{
		return Path.string();
	}

	std::string GetFileName();

	bool IsDirectory();

protected:
	std::filesystem::path Path;

private:

public:
	// 학생 추가 코드
	static std::string GetParentString(const std::string& _ChildPath);
};


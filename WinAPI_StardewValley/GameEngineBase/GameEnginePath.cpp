#include "GameEnginePath.h"
#include "GameEngineDebug.h"

GameEnginePath::GameEnginePath()
{

}

GameEnginePath::GameEnginePath(const std::string& _Path)
	:Path(_Path)
{

}

GameEnginePath::~GameEnginePath()
{

}

void GameEnginePath::GetCurrentPath()
{
	Path = std::filesystem::current_path();
}

void GameEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

std::string GameEnginePath::GetFileName()
{
	return Path.filename().string();
}


void GameEnginePath::MoveParentToExistsChild(const std::string& _ChildPath)
{
	while (true)
	{
		std::filesystem::path CheckPath = Path;
		CheckPath.append(_ChildPath);

		if (false == std::filesystem::exists(CheckPath))
		{
			MoveParent();
		}
		else
		{
			break;
		}

		if (Path.root_path() == Path)
		{
			MsgBoxAssert(Path.root_path().string() + " 까지 찾아보아도 해당 폴더가 존재하지 않습니다.");
			return;
		}
	}
}

void GameEnginePath::MoveChild(const std::string& _ChildPath)
{
	std::filesystem::path CheckPath = Path;

	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert(_ChildPath + "경로를 가진 폴더나 파일이 존재하지 않습니다.");
		return;
	}

	Path = CheckPath;
}

std::string GameEnginePath::PlusFilePath(const std::string& _ChildPath)
{
	std::filesystem::path CheckPath = Path;

	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert(_ChildPath + "경로를 가진 폴더나 파일이 존재하지 않습니다.");
	}

	return CheckPath.string();
}

bool GameEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}

#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

GameEngineDirectory::GameEngineDirectory()
{

}

GameEngineDirectory::~GameEngineDirectory()
{

}

GameEngineDirectory::GameEngineDirectory(const std::string& _Path)
	: GameEnginePath(_Path)
{
	if (false == IsDirectory())
	{
		MsgBoxAssert(_Path + "는 디렉토리 경로가 아닙니다.");
	}
}

// 현재 디렉토리의 파일만 넣음
std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(std::vector<std::string> _Ext /*= { ".Bmp" }*/)
{
	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(Path);
	std::vector<std::string> UpperFilter;
	UpperFilter.resize(_Ext.size());

	for (size_t i = 0; i < _Ext.size(); i++)
	{
		UpperFilter.push_back(GameEngineString::ToUpperReturn(_Ext[i]));
	}
	
	std::vector<GameEngineFile> Result;

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())
		{
			// 하위 폴더는 무시
			continue;
		}

		std::filesystem::path Path = Entry.path();
		std::filesystem::path Ext = Entry.path().extension();
		std::string UpperExt = GameEngineString::ToUpperReturn(Ext.string());

		bool Check = false;

		for (size_t i = 0; i < UpperFilter.size(); i++)
		{
			Check = true;
			break;
		}

		if (false == Check)
		{
			continue;
		}

		Result.push_back(GameEngineFile(Path.string()));
	}
	return Result;
}

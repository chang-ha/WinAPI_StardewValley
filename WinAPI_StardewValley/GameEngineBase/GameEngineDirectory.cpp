#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"

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
		MsgBoxAssert(_Path + "디렉토리 경로가 아닙니다.");
	}
}

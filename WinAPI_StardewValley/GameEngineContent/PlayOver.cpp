#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include "ContentsEnum.h"
#include "PlayOver.h"


PlayOver::PlayOver()
{

}

PlayOver::~PlayOver()
{

}

void PlayOver::Start()
{
	Renderer = CreateRenderer(RenderOrder::PlayOver);
}

void PlayOver::Update(float _Delta)
{
}

void PlayOver::Init(const std::string& _FileName)
{
	FileName = _FileName;
	if (false == ResourcesManager::GetInst().IsLoadTexture(FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Over\\");
		Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(FileName));
	}
	Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	Scale = Texture->GetScale();
}
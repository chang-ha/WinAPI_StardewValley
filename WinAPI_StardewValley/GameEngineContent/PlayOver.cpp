﻿#include <GameEngineCore/ResourcesManager.h>

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

void PlayOver::Render()
{

}

void PlayOver::Init(const std::string& _FileName)
{
	FileName = _FileName;
	if (false == ResourcesManager::GetInst().IsLoadTexture(FileName))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Title\\");
		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(FileName));
	}
}
﻿#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "ContentLevel.h"
#include "BackGround.h"
#include "ContentUIManager.h"
#include "TitleScreen.h"
#include "Player.h"

ContentLevel::ContentLevel()
{

}

ContentLevel::~ContentLevel()
{

}

float4 ContentLevel::GetRenderScale()
{
	return Back->GetRenderScale();
}

void ContentLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr != dynamic_cast<TitleScreen*>(this))
	{
		UIManager->Clock->Off();
		UIManager->ClockHand->Off();
		UIManager->Energy->Off();
	}
	else
	{
		UIManager->Clock->On();
		UIManager->ClockHand->On();
		UIManager->Energy->On();
	}
}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel* NextLevel = dynamic_cast<ContentLevel*>(_NextLevel);
	NextLevel->UIManager = UIManager;
}

void ContentLevel::Start()
{
	if (nullptr == UIManager)
	{
		UIManager = CreateActor<ContentUIManager>(0);
		UIManager->OverOn();
		ContentUIManager::MainUI = UIManager;
	}
}

void ContentLevel::Update(float _Delta)
{
	UIManager->ContentMouse->SetRenderPos(GameEngineWindow::MainWindow.GetMousePos());
}

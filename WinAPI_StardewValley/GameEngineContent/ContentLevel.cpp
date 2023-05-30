#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "ContentLevel.h"
#include "BackGround.h"
#include "ContentUIManager.h"
#include "TitleScreen.h"
#include "Player.h"
#include "ContentMouse.h"
#include "ContentsEnum.h"

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
	NextLevel->MainMouse = MainMouse;
}

void ContentLevel::Start()
{
	if (nullptr == UIManager)
	{
		UIManager = CreateActor<ContentUIManager>(0);
		UIManager->OverOn();
		ContentUIManager::MainUI = UIManager;

		MainMouse = CreateActor<ContentMouse>(0);
		MainMouse->Init("Cursor01.bmp");
		MainMouse->Renderer->SetTexture("Cursor01.bmp");
		MainMouse->Renderer->SetRenderScale(MainMouse->GetScale() * RENDERRATIO);
		MainMouse->MouseCollision->SetCollisionPos({-32, -32});
		MainMouse->OverOn();
	}
}

void ContentLevel::Update(float _Delta)
{
	MainMouse->SetPos(GetMainCamera()->GetPos() + GameEngineWindow::MainWindow.GetMousePos());
	
	if (true == GameEngineInput::IsDown(VK_F1))
	{
		CollisionDebugRenderSwitch();
	}
}

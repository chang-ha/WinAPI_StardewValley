#include <GameEngineBase/GameEngineTime.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "GameEngineCore.h"
#include "GameEngineLevel.h"


std::string GameEngineCore::WindowTitle = "";
std::map<std::string, GameEngineLevel*> GameEngineCore::AllLevel;
CoreProcess* GameEngineCore::Process = nullptr;
GameEngineLevel* GameEngineCore::CurLevel = nullptr;
GameEngineLevel* GameEngineCore::NextLevel = nullptr;

GameEngineCore::GameEngineCore()
{

}

GameEngineCore::~GameEngineCore()
{

}

void GameEngineCore::CoreStart(HINSTANCE _Inst)
{
	GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);
	GameEngineInput::InputInit();
	Process->Start();
}

void GameEngineCore::CoreUpdate()
{
	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->LevelEnd(NextLevel);
			CurLevel->ActorLevelEnd();
		}
		NextLevel->OverCheck(CurLevel);
		NextLevel->LevelStart(CurLevel);
		NextLevel->ActorLevelStart();

		CurLevel = NextLevel;
		NextLevel = nullptr;
		GameEngineTime::MainTimer.Reset();
	}

	GameEngineSound::Update();
	GameEngineTime::MainTimer.Update();
	float Delta = GameEngineTime::MainTimer.GetDeltaTime();

	if (true == GameEngineWindow::IsFocus())
	{
		GameEngineInput::Update(Delta);
	}
	else
	{
		GameEngineInput::Reset();
	}

	CurLevel->AddLiveTime(Delta);
	CurLevel->Update(Delta);
	CurLevel->ActorUpdate(Delta);
	GameEngineWindow::MainWindow.ClearBackBuffer();

	CurLevel->Render(Delta);
	CurLevel->ActorRender(Delta);
	GameEngineWindow::MainWindow.DoubleBuffering();

	CurLevel->ActorRelease();
}

void GameEngineCore::CoreEnd()
{
	GameEngineSound::Release();
	Process->Release();

	if (nullptr != Process)
	{
		delete Process;
		Process = nullptr;
	}

	for (std::pair<const std::string, GameEngineLevel*>& _Pair :AllLevel)
	{
		if (nullptr != _Pair.second)
		{
			delete _Pair.second;
			_Pair.second = nullptr;
		}
	}

}

void GameEngineCore::EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr)
{
	GameEngineDebug::LeckCheck();

	WindowTitle = _Title;
	Process = _Ptr;
	GameEngineWindow::MessageLoop(_Inst, CoreStart, CoreUpdate, CoreEnd);
}

void GameEngineCore::LevelInit(GameEngineLevel* _Level)
{
	_Level->Start();
}
#include <GameEngineBase/GameEngineTime.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>

#include "TitleScreen.h"
#include "BackGround.h"
#include "Player.h"
#include "TitleBird.h"
#include "PlayOver.h"
#include "ContentLevel.h"

TitleScreen::TitleScreen()
{

}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Title_background.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Title\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title_Logo.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title_new01.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title_new02.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title_load01.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title_load02.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title_coop01.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title_coop02.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title_exit01.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title_exit02.bmp"));
	}

	Back = CreateActor<BackGround>();
	Back->Init("Title_background.bmp");
	Back->Renderer->SetTexture("Title_background.bmp");
	Back->Renderer->SetRenderScale(Back->GetScale());
	Back->SetRenderScale(Back->GetScale());
	Back->SetPos({740,300});

	TitleBird* Bird1 = CreateActor<TitleBird>();
	TitleBird* Bird2 = CreateActor<TitleBird>();
	Bird1->SetPos({ 1200, 700 });
	Bird2->SetPos({1300,775});

	Logo = CreateActor<PlayOver>();
	Logo->Init("Title_Logo.bmp");
	Logo->Renderer->SetTexture("Title_Logo.bmp");
	Logo->Renderer->SetRenderScale(Logo->GetScale() * 2);
	Logo->SetPos({800, -70});
	Logo->Renderer->Off();

	New_Button = CreateActor<PlayOver>();
	New_Button->Init("Title_new01.bmp");
	New_Button->Renderer->SetTexture("Title_new01.bmp");
	New_Button->Renderer->SetRenderScale(New_Button->GetScale() * 2.5); // X 2.5
	New_Button->SetPos({375, 330});
	New_Button->Renderer->Off();

	Load_Button = CreateActor<PlayOver>();
	Load_Button->Init("Title_load01.bmp");
	Load_Button->Renderer->SetTexture("Title_load01.bmp");
	Load_Button->Renderer->SetRenderScale(Load_Button->GetScale() * 2.5); // X 2.5
	Load_Button->SetPos({ 658, 330 }); // 185 + 98
	Load_Button->Renderer->Off();

	Coop_Button = CreateActor<PlayOver>();
	Coop_Button->Init("Title_coop01.bmp");
	Coop_Button->Renderer->SetTexture("Title_coop01.bmp");
	Coop_Button->Renderer->SetRenderScale(Coop_Button->GetScale() *2.5); // X 2.5
	Coop_Button->SetPos({ 941, 330 });
	Coop_Button->Renderer->Off();

	Exit_Button = CreateActor<PlayOver>();
	Exit_Button->Init("Title_exit01.bmp");
	Exit_Button->Renderer->SetTexture("Title_exit01.bmp");
	Exit_Button->Renderer->SetRenderScale(Exit_Button->GetScale() *2.5); // X 2.5
	Exit_Button->SetPos({1225, 330 });
	Exit_Button->Renderer->Off();
}
void TitleScreen::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("FarmHouse");
	}
	if (3.0f < Back->GetLiveTime())
	{
		if (-300 <= GetMainCamera()->GetPos().iY())
		{
			float4 MovePos = float4::UP;
			MovePos *= 50.0f;
			GetMainCamera()->AddPos(MovePos * _DeltaTime);
		}
		else if (true)
		{
			Logo->Renderer->On();
			New_Button->Renderer->On();
			Load_Button->Renderer->On();
			Coop_Button->Renderer->On();
			Exit_Button->Renderer->On();
		}
	}

	float4 MovePos = float4::ZERO;
	float Speed = 1000000.0f;

	if (true == GameEngineInput::IsPress('A') /*&& Dir == PlayerDir::Left*/)
	{
		MovePos = { -Speed * _DeltaTime, 0.0f };
	}

	if (true == GameEngineInput::IsPress('D') /*&& Dir == PlayerDir::Right*/)
	{
		MovePos = { Speed * _DeltaTime, 0.0f };
	}

	if (true == GameEngineInput::IsPress('W') /*&& Dir == PlayerDir::Up*/)
	{
		MovePos = { 0.0f, -Speed * _DeltaTime };
	}

	if (true == GameEngineInput::IsPress('S') /*&& Dir == PlayerDir::Down*/)
	{
		MovePos = { 0.0f, Speed * _DeltaTime };
	}

	GetMainCamera()->AddPos(MovePos * _DeltaTime);
}
void TitleScreen::Render()
{

}
void TitleScreen::Release()
{
}

void TitleScreen::LevelStart(GameEngineLevel* _PrevLevel)
{

}
void TitleScreen::LevelEnd(GameEngineLevel* _NextLevel)
{
}
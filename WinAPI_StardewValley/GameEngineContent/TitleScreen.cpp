#include <GameEngineBase/GameEngineTime.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>

#include "TitleScreen.h"
#include "BackGround.h"
#include "Player.h"
#include "PlayOver.h"
#include "ContentLevel.h"
#include "Creature.h"

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
		FilePath.MoveChild("Resources\\Textures\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\Title_Logo.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\Title_new01.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\Title_new02.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\Title_load01.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\Title_load02.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\Title_coop01.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\Title_coop02.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\Title_exit01.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\Title_exit02.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\Title_LeftTree.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\Title_RightTree.bmp"));

		ResourcesManager::GetInst().CreateSpriteSheet("Title_Bird", FilePath.PlusFilePath("Creature\\Title_Bird.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Title_Bird1", FilePath.PlusFilePath("Creature\\Title_Bird1.bmp"), 6, 1);
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	Back = CreateActor<BackGround>(0);
	Back->Init("Title_background.bmp");
	Back->Renderer->SetTexture("Title_background.bmp");
	Back->Renderer->SetRenderScale(Back->GetScale() * 1.2f);
	Back->SetRenderScale(Back->GetScale() * 1.2f);
	Back->SetPos({WinScale.Half().X, WinScale.Y - Back->GetRenderScale().Half().Y});

	Logo = CreateActor<PlayOver>();
	Logo->Init("Title_Logo.bmp");
	Logo->Renderer->SetTexture("Title_Logo.bmp");
	Logo->Renderer->SetRenderScale(Logo->GetScale() * 2.5f);
	Logo->SetPos({800, -250});

	New_Button = CreateActor<PlayOver>();
	New_Button->Init("Title_new01.bmp");
	New_Button->Renderer->SetTexture("Title_new01.bmp");
	New_Button->Renderer->SetRenderScale(New_Button->GetScale() * 3.0f);
	New_Button->SetPos({375, 200});
	New_Button->Renderer->Off();

	Load_Button = CreateActor<PlayOver>();
	Load_Button->Init("Title_load01.bmp");
	Load_Button->Renderer->SetTexture("Title_load01.bmp");
	Load_Button->Renderer->SetRenderScale(Load_Button->GetScale() * 3.0f);
	Load_Button->SetPos({ 658, 200 }); // 185 + 98
	Load_Button->Renderer->Off();

	Coop_Button = CreateActor<PlayOver>();
	Coop_Button->Init("Title_coop01.bmp");
	Coop_Button->Renderer->SetTexture("Title_coop01.bmp");
	Coop_Button->Renderer->SetRenderScale(Coop_Button->GetScale() * 3.0f);
	Coop_Button->SetPos({ 941, 200 });
	Coop_Button->Renderer->Off();

	Exit_Button = CreateActor<PlayOver>();
	Exit_Button->Init("Title_exit01.bmp");
	Exit_Button->Renderer->SetTexture("Title_exit01.bmp");
	Exit_Button->Renderer->SetRenderScale(Exit_Button->GetScale() * 3.0f);
	Exit_Button->SetPos({1225, 200 });
	Exit_Button->Renderer->Off();

	{
		LeftTree = CreateActor<PlayOver>();
		LeftTree->Init("Title_LeftTree.bmp");
		LeftTree->Renderer->SetTexture("Title_LeftTree.bmp");
		LeftTree->Renderer->SetRenderScale(LeftTree->GetScale() * 3.0f);
		LeftTree->SetRenderScale(LeftTree->GetScale() * 3.0f);
		LeftTree->SetPos({ LeftTree->GetRenderScale().Half().X, WinScale.Y - LeftTree->GetRenderScale().Half().Y + 10});

		RightTree = CreateActor<PlayOver>();
		RightTree->Init("Title_LeftTree.bmp");
		RightTree->Renderer->SetTexture("Title_RightTree.bmp");
		RightTree->Renderer->SetRenderScale(RightTree->GetScale() * 3.0f);
		RightTree->SetRenderScale(RightTree->GetScale() * 3.0f);
		RightTree->SetPos({ WinScale.X - RightTree->GetRenderScale().Half().X, WinScale.Y - RightTree->GetRenderScale().Half().Y + 10 });
	}

	{
		Bird1 = CreateActor<Creature>();
		Bird2 = CreateActor<Creature>();
		
		Bird1->Renderer->SetScaleRatio(3.0f);
		Bird1->Renderer->CreateAnimation("Bird_Idle","Title_Bird");
		Bird1->Renderer->ChangeAnimation("Bird_Idle");
		Bird2->Renderer->SetScaleRatio(3.0f);
		Bird2->Renderer->CreateAnimation("Bird_Idle1", "Title_Bird1");
		Bird2->Renderer->ChangeAnimation("Bird_Idle1");
		Bird1->SetPos({ 1325, 700 });
		Bird2->SetPos({ 1400, 750 });
	}
}

void TitleScreen::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("FarmHouse");
	}

	float4 Speed = float4::UP;
	if (4.0f < Back->GetLiveTime())
	{
		if (GameEngineWindow::MainWindow.GetScale().Y - Back->GetRenderScale().Y <= GetMainCamera()->GetPos().iY())
		{
			Speed *= 80.0f;
			GetMainCamera()->AddPos(Speed * _DeltaTime);
		}
		else if (true)
		{
			New_Button->Renderer->On();
			Load_Button->Renderer->On();
			Coop_Button->Renderer->On();
			Exit_Button->Renderer->On();
		}
	}
	
	{
		Bird1->AddPos({ -50.0f * _DeltaTime, 0.0f });
		Bird2->AddPos({ -50.0f * _DeltaTime, 0.0f });
	}
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
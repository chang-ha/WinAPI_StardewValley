#define BUTTONTIME 0.2f;

#include <GameEngineBase/GameEngineTime.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "TitleScreen.h"
#include "BackGround.h"
#include "Player.h"
#include "PlayOver.h"
#include "ContentLevel.h"
#include "Creature.h"
#include "ContentsEnum.h"

TitleScreen::TitleScreen()
{

}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::LevelStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineSound::SoundPlay("Title.mp3", 10000);
	BGMPlayer.SetVolume(0.4f);

	// Reset TitleScreen
	Back->ResetLiveTime();
	GetMainCamera()->SetPos({ Back->GetPos().X - WinScale.Half().X, Back->GetRenderScale().Y - WinScale.Y });
	IsSkip = false;
	Speed = {};

	New_Button->Renderer->Off();
	Load_Button->Renderer->Off();
	Coop_Button->Renderer->Off();
	Exit_Button->Renderer->Off();

	New_Button->Collision->Off();
	Load_Button->Collision->Off();
	Coop_Button->Collision->Off();
	Exit_Button->Collision->Off();

	Bird1->SetPos({ GetMainCamera()->GetPos().X + WinScale.X * 0.80f, GetMainCamera()->GetPos().Y + WinScale.Y * 0.75f });
	Bird2->SetPos({ GetMainCamera()->GetPos().X + WinScale.X * 0.80f - 100, GetMainCamera()->GetPos().Y + WinScale.Y * 0.75f - 50});
	ContentLevel::LevelStart(_PrevLevel);
}

void TitleScreen::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	BGMPlayer.Stop();
}

void TitleScreen::Start()
{
	ContentLevel::Start();
	NextLevel = "FarmHouse";
	// Texture Load
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

		ResourcesManager::GetInst().CreateSpriteSheet("Title_LeftLeaf", FilePath.PlusFilePath("Title\\Title_LeftLeaf.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Title_RightLeaf", FilePath.PlusFilePath("Title\\Title_RightLeaf.bmp"), 5, 1);

		ResourcesManager::GetInst().CreateSpriteSheet("Title_Bird", FilePath.PlusFilePath("Creature\\Title_Bird.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Title_Bird1", FilePath.PlusFilePath("Creature\\Title_Bird1.bmp"), 6, 1);
	}

	// Music Load
	if (nullptr == GameEngineSound::FindSound("Title.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BGM\\Title.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Effect\\select.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Effect\\Button_Over.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Effect\\Button_On.wav"));
		GameEngineSound::SetGlobalVolume(0.9f);
	}

	// BackGround
	Back = CreateActor<BackGround>(0);
	Back->Init("Title_background.bmp");
	Back->Renderer->SetTexture("Title_background.bmp");
	Back->Renderer->SetRenderScale(Back->GetScale() * 1.2f);
	Back->SetRenderScale(Back->GetScale() * 1.2f);
	Back->SetPos(GetRenderScale().Half());

	GetMainCamera()->SetPos({Back->GetPos().X - WinScale.Half().X, Back->GetRenderScale().Y - WinScale.Y});
	// Title Button
	{
		Logo = CreateActor<PlayOver>();
		Logo->Init("Title_Logo.bmp");
		Logo->Renderer->SetTexture("Title_Logo.bmp");
		Logo->Renderer->SetRenderScale(Logo->GetScale() * 2.5f);
		Logo->SetRenderScale(Logo->GetScale() * 2.5f);
		Logo->SetPos({ Back->GetPos().X, Logo->GetRenderScale().Half().Y + 40});

		New_Button = CreateActor<PlayOver>();
		New_Button->Init("Title_new01.bmp");
		New_Button->Renderer->SetRenderScale(New_Button->GetScale() * RENDERRATIO);
		New_Button->SetRenderScale(New_Button->GetScale() * RENDERRATIO);
		New_Button->SetPos({ GetMainCamera()->GetPos().X + WinScale.X * 0.2f, WinScale.Y - New_Button->GetRenderScale().Half().Y - 50 });
		New_Button->Renderer->Off();

		Load_Button = CreateActor<PlayOver>();
		Load_Button->Init("Title_load01.bmp");
		Load_Button->Renderer->SetRenderScale(Load_Button->GetScale() * RENDERRATIO);
		Load_Button->SetRenderScale(Load_Button->GetScale() * RENDERRATIO);
		Load_Button->SetPos({ GetMainCamera()->GetPos().X + WinScale.X * 0.4f, WinScale.Y - Load_Button->GetRenderScale().Half().Y - 50 });
		Load_Button->Renderer->Off();

		Coop_Button = CreateActor<PlayOver>();
		Coop_Button->Init("Title_coop01.bmp");
		Coop_Button->Renderer->SetRenderScale(Coop_Button->GetScale() * RENDERRATIO);
		Coop_Button->SetRenderScale(Coop_Button->GetScale() * RENDERRATIO);
		Coop_Button->SetPos({ GetMainCamera()->GetPos().X + WinScale.X * 0.6f, WinScale.Y - Coop_Button->GetRenderScale().Half().Y - 50 });
		Coop_Button->Renderer->Off();

		Exit_Button = CreateActor<PlayOver>();
		Exit_Button->Init("Title_exit01.bmp");
		Exit_Button->Renderer->SetRenderScale(Exit_Button->GetScale() * RENDERRATIO);
		Exit_Button->SetRenderScale(Exit_Button->GetScale() * RENDERRATIO);
		Exit_Button->SetPos({ GetMainCamera()->GetPos().X + WinScale.X * 0.8f, WinScale.Y - Exit_Button->GetRenderScale().Half().Y - 50 });
		Exit_Button->Renderer->Off();

		// Create Button Collision
		New_Button->Collision = New_Button->CreateCollision(CollisionOrder::Button);
		New_Button->Collision->SetCollisionScale(New_Button->GetScale() * RENDERRATIO);
		New_Button->Collision->Off();

		Load_Button->Collision = Load_Button->CreateCollision(CollisionOrder::Button);
		Load_Button->Collision->SetCollisionScale(Load_Button->GetScale() * RENDERRATIO);
		Load_Button->Collision->Off();

		Coop_Button->Collision = Coop_Button->CreateCollision(CollisionOrder::Button);
		Coop_Button->Collision->SetCollisionScale(Coop_Button->GetScale() * RENDERRATIO);
		Coop_Button->Collision->Off();

		Exit_Button->Collision = Exit_Button->CreateCollision(CollisionOrder::Button);
		Exit_Button->Collision->SetCollisionScale(Exit_Button->GetScale() * RENDERRATIO);
		Exit_Button->Collision->Off();
	}

	// Detail
	{
		LeftTree = CreateActor<PlayOver>();
		RightTree = CreateActor<PlayOver>();
		LeftLeaf = CreateActor<PlayOver>();
		RightLeaf = CreateActor<PlayOver>();
		Bird1 = CreateActor<Creature>();
		Bird2 = CreateActor<Creature>();

		LeftTree->Init("Title_LeftTree.bmp");
		LeftTree->Renderer->SetTexture("Title_LeftTree.bmp");
		LeftTree->Renderer->SetRenderScale(LeftTree->GetScale() * RENDERRATIO);
		LeftTree->SetRenderScale(LeftTree->GetScale() * RENDERRATIO);
		LeftTree->SetPos({ GetMainCamera()->GetPos().X + LeftTree->GetRenderScale().Half().X, Back->GetRenderScale().Y - LeftTree->GetRenderScale().Half().Y});

		RightTree->Init("Title_RightTree.bmp");
		RightTree->Renderer->SetTexture("Title_RightTree.bmp");
		RightTree->Renderer->SetRenderScale(RightTree->GetScale() * RENDERRATIO);
		RightTree->SetRenderScale(RightTree->GetScale() * RENDERRATIO);
		RightTree->SetPos({ GetMainCamera()->GetPos().X + WinScale.X - RightTree->GetRenderScale().Half().X, Back->GetRenderScale().Y - RightTree->GetRenderScale().Half().Y });

		LeftLeaf->Renderer->SetScaleRatio(2.5f);
		LeftLeaf->Renderer->CreateAnimation("LeftLeaf_Move", "Title_LeftLeaf", 0, 4, 0.2f, false);
		LeftLeaf->Renderer->ChangeAnimation("LeftLeaf_Move");
		LeftLeaf->SetPos(Logo->GetPos() - Logo->GetRenderScale().Half() + float4{69,59});

		RightLeaf->Renderer->SetScaleRatio(2.5f);
		RightLeaf->Renderer->CreateAnimation("RightLeaf_Move", "Title_RightLeaf", 0, 4, 0.2f, false);
		RightLeaf->Renderer->ChangeAnimation("RightLeaf_Move");
		RightLeaf->SetPos(Logo->GetPos() + Logo->GetRenderScale().Half() + float4{-150, -175});

		Bird1->Renderer->SetScaleRatio(RENDERRATIO);
		Bird1->Renderer->CreateAnimation("Bird_Idle","Title_Bird");
		Bird1->Renderer->ChangeAnimation("Bird_Idle");

		Bird2->Renderer->SetScaleRatio(RENDERRATIO);
		Bird2->Renderer->CreateAnimation("Bird_Idle1", "Title_Bird1");
		Bird2->Renderer->ChangeAnimation("Bird_Idle1");
	}
}

void TitleScreen::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	// Camera Update
	if (4.0f < Back->GetLiveTime())
	{
		if (-60.0f < Speed.Y)
		{
			Speed += {0, -15.0f * _Delta};
		}

		static float CheckTime = BUTTONTIME;
		if (0 <= GetMainCamera()->GetPos().iY())
		{
			GetMainCamera()->AddPos(Speed * _Delta);
		}
		else if (false == New_Button->Renderer->IsUpdate() && CheckTime <= 0.0f)
		{
			EffectPlayer = GameEngineSound::SoundPlay("Button_On.wav");
			New_Button->Renderer->On();
			New_Button->Collision->On();
			IsSkip = true;
			CheckTime = BUTTONTIME;
		}
		else if (false == Load_Button->Renderer->IsUpdate() && CheckTime <= 0.0f)
		{
			EffectPlayer = GameEngineSound::SoundPlay("Button_On.wav");
			Load_Button->Renderer->On();
			Load_Button->Collision->On();
			CheckTime = BUTTONTIME;
		}
		else if (false == Coop_Button->Renderer->IsUpdate() && CheckTime <= 0.0f)
		{
			EffectPlayer = GameEngineSound::SoundPlay("Button_On.wav");
			Coop_Button->Renderer->On();
			Coop_Button->Collision->On();
			CheckTime = BUTTONTIME;
		}
		else if (false == Exit_Button->Renderer->IsUpdate() && CheckTime <= 0.0f)
		{
			EffectPlayer = GameEngineSound::SoundPlay("Button_On.wav");
			Exit_Button->Renderer->On();
			Exit_Button->Collision->On();
			CheckTime = BUTTONTIME;
		}
		CheckTime -= _Delta;
	}
	
	// Mouse Click To Skip
	if (4.0f < Back->GetLiveTime() && true == GameEngineInput::IsDown(VK_LBUTTON) && false == IsSkip)
	{
		GetMainCamera()->SetPos({ Back->GetPos().X - WinScale.Half().X, 0 });
	} 
	
	// Detail Update
	static float LeftLeafTime = 3.0f;
	static float RightLeafTime = 5.0f;
	if (0.0f >= LeftLeafTime)
	{
		LeftLeaf->Renderer->ChangeAnimation("LeftLeaf_Move", 0, true);
		LeftLeafTime = 3.0f;
	}
		
	if (0.0f >= RightLeafTime)
	{
		RightLeaf->Renderer->ChangeAnimation("RightLeaf_Move", 0, true);
		RightLeafTime = 5.0f;
	}
	LeftLeafTime -= _Delta;
	RightLeafTime -= _Delta;

	Bird1->AddPos({ -50.0f * _Delta, 0.0f });
	Bird2->AddPos({ -50.0f * _Delta, 0.0f });

	// Collision Check
	New_Button->Renderer->SetTexture("Title_new01.bmp");
	Load_Button->Renderer->SetTexture("Title_load01.bmp");
	Coop_Button->Renderer->SetTexture("Title_coop01.bmp");
	Exit_Button->Renderer->SetTexture("Title_exit01.bmp");

	std::vector<GameEngineCollision*> _CheckCollision;
	if (true == MainMouse->GetMouseCollision()->Collision(CollisionOrder::Button, _CheckCollision, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineCollision* CheckCollision = _CheckCollision[0];
		GameEngineActor* Actor = CheckCollision->GetActor();
		PlayOver* TitleButton = dynamic_cast<PlayOver*>(Actor);

		if (TitleButton == nullptr)
		{
			MsgBoxAssert("Collision충돌이 잘못되었습니다.");
			return;
		}

		if (false == IsMouseOn)
		{
			EffectPlayer = GameEngineSound::SoundPlay("Button_Over.wav");
			IsMouseOn = true;
		}

		if ("Title_new01.bmp" == TitleButton->GetFileName())
		{
			TitleButton->Renderer->SetTexture("Title_new02.bmp");
			if (true == GameEngineInput::IsDown(VK_LBUTTON))
			{
				GameEngineCore::ChangeLevel("FarmHouse");
				EffectPlayer = GameEngineSound::SoundPlay("select.wav");
			}
		}
		else if ("Title_load01.bmp" == TitleButton->GetFileName())
		{
			TitleButton->Renderer->SetTexture("Title_load02.bmp");
		}
		else if ("Title_coop01.bmp" == TitleButton->GetFileName())
		{
			TitleButton->Renderer->SetTexture("Title_coop02.bmp");
		}
		else if ("Title_exit01.bmp" == TitleButton->GetFileName())
		{
			TitleButton->Renderer->SetTexture("Title_exit02.bmp");
			if (true == GameEngineInput::IsDown(VK_LBUTTON))
			{
				GameEngineWindow::MainWindow.WindowUpdateOff();
			}
		}
	}
	else
	{
		IsMouseOn = false;
	}
}
void TitleScreen::Render(float _Delta)
{

}
void TitleScreen::Release()
{
}


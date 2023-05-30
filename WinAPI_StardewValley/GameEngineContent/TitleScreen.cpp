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
	ContentLevel::LevelStart(_PrevLevel);
	BGMPlayer = GameEngineSound::SoundPlay("Title.mp3");

	// Reset TitleScreen
	GetMainCamera()->SetPos({});
	Back->ResetLiveTime();
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


	Bird1->SetPos({ 1200, 600 });
	Bird2->SetPos({ 1285, 650 });
}

void TitleScreen::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	BGMPlayer.Stop();
}

void TitleScreen::Start()
{
	ContentLevel::Start();
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
		// ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\BigCloud.bmp"));
		// ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\MiddleCloud.bmp"));
		// ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Title\\SmallCloud.bmp"));

		ResourcesManager::GetInst().CreateSpriteSheet("Title_LeftLeaf", FilePath.PlusFilePath("Title\\Title_LeftLeaf.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Title_RightLeaf", FilePath.PlusFilePath("Title\\Title_RightLeaf.bmp"), 5, 1);

		ResourcesManager::GetInst().CreateSpriteSheet("Title_Bird", FilePath.PlusFilePath("Creature\\Title_Bird.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Title_Bird1", FilePath.PlusFilePath("Creature\\Title_Bird1.bmp"), 6, 1);

		GameEngineWindow::MainWindow.CursorOff();
	}

	// Music Load
	if (nullptr == GameEngineSound::FindSound("Title.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\BGM");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Title.mp3"));
		GameEngineSound::SetGlobalVolume(0.5f);
	}

	// BackGround
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	Back = CreateActor<BackGround>(0);
	Back->Init("Title_background.bmp");
	Back->Renderer->SetTexture("Title_background.bmp");
	Back->Renderer->SetRenderScale(Back->GetScale() * 1.2f);
	Back->SetRenderScale(Back->GetScale() * 1.2f);
	Back->SetPos({WinScale.Half().X, WinScale.Y - Back->GetRenderScale().Half().Y});

	// Title Button
	{
		Logo = CreateActor<PlayOver>();
		Logo->Init("Title_Logo.bmp");
		Logo->Renderer->SetTexture("Title_Logo.bmp");
		Logo->Renderer->SetRenderScale(Logo->GetScale() * 2.5f);
		Logo->SetPos({ 800, -250 });

		New_Button = CreateActor<PlayOver>();
		New_Button->Init("Title_new01.bmp");
		New_Button->Renderer->SetRenderScale(New_Button->GetScale() * 3.0f);
		New_Button->SetPos({ 375, 200 });
		New_Button->Renderer->Off();

		Load_Button = CreateActor<PlayOver>();
		Load_Button->Init("Title_load01.bmp");
		Load_Button->Renderer->SetRenderScale(Load_Button->GetScale() * 3.0f);
		Load_Button->SetPos({ 658, 200 }); // 185 + 98
		Load_Button->Renderer->Off();

		Coop_Button = CreateActor<PlayOver>();
		Coop_Button->Init("Title_coop01.bmp");
		Coop_Button->Renderer->SetRenderScale(Coop_Button->GetScale() * 3.0f);
		Coop_Button->SetPos({ 941, 200 });
		Coop_Button->Renderer->Off();

		Exit_Button = CreateActor<PlayOver>();
		Exit_Button->Init("Title_exit01.bmp");
		Exit_Button->Renderer->SetRenderScale(Exit_Button->GetScale() * 3.0f);
		Exit_Button->SetPos({ 1225, 200 });
		Exit_Button->Renderer->Off();

		// Create Collision
		New_Button->Collision = New_Button->CreateCollision(CollisionOrder::Button);
		New_Button->Collision->SetCollisionScale(New_Button->GetScale() * 3.0f);
		New_Button->Collision->Off();

		Load_Button->Collision = Load_Button->CreateCollision(CollisionOrder::Button);
		Load_Button->Collision->SetCollisionScale(Load_Button->GetScale() * 3.0f);
		Load_Button->Collision->Off();

		Coop_Button->Collision = Coop_Button->CreateCollision(CollisionOrder::Button);
		Coop_Button->Collision->SetCollisionScale(Coop_Button->GetScale() * 3.0f);
		Coop_Button->Collision->Off();

		Exit_Button->Collision = Exit_Button->CreateCollision(CollisionOrder::Button);
		Exit_Button->Collision->SetCollisionScale(Exit_Button->GetScale() * 3.0f);
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
		// LargeCloud1 = CreateActor<Creature>();
		// LargeCloud2 = CreateActor<Creature>();

		LeftTree->Init("Title_LeftTree.bmp");
		LeftTree->Renderer->SetTexture("Title_LeftTree.bmp");
		LeftTree->Renderer->SetRenderScale(LeftTree->GetScale() * 3.0f);
		LeftTree->SetRenderScale(LeftTree->GetScale() * 3.0f);
		LeftTree->SetPos({ LeftTree->GetRenderScale().Half().X, WinScale.Y - LeftTree->GetRenderScale().Half().Y + 10});

		RightTree->Init("Title_RightTree.bmp");
		RightTree->Renderer->SetTexture("Title_RightTree.bmp");
		RightTree->Renderer->SetRenderScale(RightTree->GetScale() * 3.0f);
		RightTree->SetRenderScale(RightTree->GetScale() * 3.0f);
		RightTree->SetPos({ WinScale.X - RightTree->GetRenderScale().Half().X, WinScale.Y - RightTree->GetRenderScale().Half().Y + 10 });

		// LargeCloud1->Init("BigCloud.bmp");
		// LargeCloud1->Renderer->SetTexture("BigCloud.bmp");
		// LargeCloud1->Renderer->SetRenderScale(LargeCloud1->GetScale() * 3.0f);
		// LargeCloud1->SetPos({1600,270 });
		
		// LargeCloud2->Init("BigCloud.bmp");
		// LargeCloud2->Renderer->SetTexture("BigCloud.bmp");
		// LargeCloud2->Renderer->SetRenderScale(LargeCloud2->GetScale() * 3.0f);
		// LargeCloud2->SetPos({ 1000,70 });

		LeftLeaf->Renderer->SetScaleRatio(2.5f);
		LeftLeaf->Renderer->CreateAnimation("LeftLeaf_Move", "Title_LeftLeaf", 0, 4, 0.2f, false);
		LeftLeaf->Renderer->ChangeAnimation("LeftLeaf_Move");
		LeftLeaf->SetPos({ 370, -423 });

		RightLeaf->Renderer->SetScaleRatio(2.5f);
		RightLeaf->Renderer->CreateAnimation("RightLeaf_Move", "Title_RightLeaf", 0, 4, 0.2f, false);
		RightLeaf->Renderer->ChangeAnimation("RightLeaf_Move");
		RightLeaf->SetPos({ 1148, -190 });

		Bird1->Renderer->SetScaleRatio(3.0f);
		Bird1->Renderer->CreateAnimation("Bird_Idle","Title_Bird");
		Bird1->Renderer->ChangeAnimation("Bird_Idle");

		Bird2->Renderer->SetScaleRatio(3.0f);
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

		if (GameEngineWindow::MainWindow.GetScale().Y - Back->GetRenderScale().Y <= GetMainCamera()->GetPos().iY())
		{
			GetMainCamera()->AddPos(Speed * _Delta);
		}
		else if (true)
		{
			New_Button->Renderer->On();
		 	Load_Button->Renderer->On();
			Coop_Button->Renderer->On();
			Exit_Button->Renderer->On();

			New_Button->Collision->On();
			Load_Button->Collision->On();
			Coop_Button->Collision->On();
			Exit_Button->Collision->On();

			IsSkip = true;
		}
	}
	
	// Mouse Click To Skip
	if (4.0f < Back->GetLiveTime() && true == GameEngineInput::IsDown(VK_LBUTTON) && false == IsSkip)
	{
		GetMainCamera()->SetPos({ 0, GameEngineWindow::MainWindow.GetScale().Y - Back->GetRenderScale().Y });
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
		RightLeafTime = 3.0f;
	}
	LeftLeafTime -= _Delta;
	RightLeafTime -= _Delta;

	{
		Bird1->AddPos({ -50.0f * _Delta, 0.0f });
		Bird2->AddPos({ -50.0f * _Delta, 0.0f });
		// LargeCloud1->AddPos({ -10.0f * _Delta, 0.0f });
		// LargeCloud2->AddPos({ -10.0f * _Delta, 0.0f });
	}

	// Collision Check
	{
		New_Button->Renderer->SetTexture("Title_new01.bmp");
		Load_Button->Renderer->SetTexture("Title_load01.bmp");
		Coop_Button->Renderer->SetTexture("Title_coop01.bmp");
		Exit_Button->Renderer->SetTexture("Title_exit01.bmp");

		std::vector<GameEngineCollision*> _CheckCollision;
		if (true == MainMouse->MouseCollision->Collision(CollisionOrder::Button, _CheckCollision, CollisionType::Rect, CollisionType::Rect))
		{
			GameEngineCollision* CheckCollision = _CheckCollision[0];
			GameEngineActor* Actor = CheckCollision->GetActor();

			PlayOver* TitleButton = dynamic_cast<PlayOver*>(Actor);
			if (nullptr == TitleButton)
			{
				MsgBoxAssert("Collision충돌이 잘못되었습니다.");
			}

			std::string ButtonName = TitleButton->GetFileName();
			if ("Title_new01.bmp" == ButtonName)
			{
				TitleButton->Renderer->SetTexture("Title_new02.bmp");
				if (true == GameEngineInput::IsDown(VK_LBUTTON))
				{
					GameEngineCore::ChangeLevel("FarmHouse");
				}
			}
			else if ("Title_load01.bmp" == ButtonName)
			{
				TitleButton->Renderer->SetTexture("Title_load02.bmp");
			}
			else if ("Title_coop01.bmp" == ButtonName)
			{
				TitleButton->Renderer->SetTexture("Title_coop02.bmp");
			}
			else if ("Title_exit01.bmp" == ButtonName)
			{
				TitleButton->Renderer->SetTexture("Title_exit02.bmp");
				if (true == GameEngineInput::IsDown(VK_LBUTTON))
				{
					GameEngineWindow::MainWindow.WindowUpdateOff();
				}
			}
		}
	}
}
void TitleScreen::Render(float _Delta)
{

}
void TitleScreen::Release()
{
}


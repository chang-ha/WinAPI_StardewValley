#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "EndingLevel.h"
#include "ContentsEnum.h"
#include "BackGround.h"
#include "GlobalValue.h"
#include "PlayOver.h"
#include "ContentUIManager.h"
#include "EndingActor.h"

EndingLevel::EndingLevel()
{

}

EndingLevel::~EndingLevel()
{

}

void EndingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
	BGMPlayer = GameEngineSound::SoundPlay("Ending.wav");
	BGMPlayer.SetVolume(0.8f);
	ContentUIManager::MainUI->BasicUIOff();
}

void EndingLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void EndingLevel::Start()
{
	if (nullptr == Back)
	{
		// BackGround
		Back = CreateActor<BackGround>(UpdateOrder::Map);
		Back->Init("EndCredit.bmp");
		Back->GetRenderer()->SetRenderScale(GlobalValue::WinScale);
		Back->SetPos(GlobalValue::WinScale.Half());
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("UI_Skip.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\UI");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI_Skip.bmp"));
	}

	// Sound Load
	if (nullptr == GameEngineSound::FindSound("Ending.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\BGM");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Ending.wav"));
	}

	// Ending UI
	CatrgoryActor = CreateActor<PlayOver>();
	CatrgoryActor->GetRenderer()->SetText("ÀÌ¿ô", 40, "Sandoll ¹Ì»ý");
	CatrgoryActor->GetRenderer()->ChangeTextColor(RGB(255, 255, 255));
	CatrgoryActor->SetPos({GlobalValue::WinScale.hX(), GlobalValue::WinScale.Y * 0.8f});
	CatrgoryActor->Off();

	PlayOver* SkipButton = CreateActor<PlayOver>();
	SkipButton->Init("UI_Skip.bmp");
	SkipButton->SetPos({ GlobalValue::WinScale.X - SkipButton->GetRenderScale().X, GlobalValue::WinScale.Y - SkipButton->GetRenderScale().Y });

	SkipButtonCollision = SkipButton->CreateCollision(CollisionOrder::Button);
	SkipButtonCollision->SetCollisionScale(SkipButton->GetRenderScale());

	// Ending Actor
	EndingActor* EndActor = CreateActor<EndingActor>();
	EndActor->SetPos({GlobalValue::WinScale.X, GlobalValue::WinScale.hY()});
	EndActor->InitAnimation("Npc1");
}

void EndingLevel::Update(float _Delta)
{
	if (true == SkipButtonCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect)
		&& true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		GameEngineWindow::MainWindow.WindowUpdateOff();
	}
}

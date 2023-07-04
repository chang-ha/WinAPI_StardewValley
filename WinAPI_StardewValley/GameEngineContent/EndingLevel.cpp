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
	CategoryActor = CreateActor<PlayOver>();
	CategoryActor->GetRenderer()->SetText("�̿�", 40, "Sandoll �̻�");
	CategoryActor->GetRenderer()->ChangeTextColor(RGB(255, 255, 255));
	CategoryActor->SetPos({GlobalValue::WinScale.hX(), GlobalValue::WinScale.Y * 0.8f});
	CategoryActor->Off();

	PlayOver* SkipButton = CreateActor<PlayOver>();
	SkipButton->Init("UI_Skip.bmp");
	SkipButton->SetPos({ GlobalValue::WinScale.X - SkipButton->GetRenderScale().X, GlobalValue::WinScale.Y - SkipButton->GetRenderScale().Y });

	SkipButtonCollision = SkipButton->CreateCollision(CollisionOrder::Button);
	SkipButtonCollision->SetCollisionScale(SkipButton->GetRenderScale());

	// Ending Actor

	// Neighbor
	float4 TempPos = { GlobalValue::WinScale.X, GlobalValue::WinScale.hY() };
	for (int i = 0; i < 30; i++)
	{
		EndingActor* EndActor = CreateActor<EndingActor>();
		EndActor->SetPos(TempPos + float4{TILESIZE.X * 3.0f, 0});
		TempPos = EndActor->GetPos();
		EndActor->InitAnimation("Npc" + std::to_string(1));
	}

	TempPos.X += TILESIZE.X * 15.0f;
	for (int i = 0; i < 4; i++)
	{
		EndingActor* EndActor = CreateActor<EndingActor>();
		EndActor->SetPos(TempPos + float4{TILESIZE.X * 3.0f, 0});
		TempPos = EndActor->GetPos();
		EndActor->InitAnimation("Npc" + std::to_string(1));
	}

	TempPos.X += TILESIZE.X * 15.0f;
	TempPos.Y += TILESIZE.Y * 2.0f;
	std::vector<std::string> NameText;
	NameText.resize(13);
	NameText[0] = ("�� ��");
	NameText[1] = ("���� ��");
	NameText[2] = ("�Ķ� ��");
	NameText[3] = ("���� ��");
	NameText[4] = ("Ȳ�� ��");
	NameText[5] = ("����");
	NameText[6] = ("�䳢");
	NameText[7] = ("����");
	NameText[8] = ("�� ��");
	NameText[9] = ("����");
	NameText[10] = ("����");
	NameText[11] = ("��");
	NameText[12] = ("Ÿ��");
	for (int i = 0; i < 13; i++)
	{
		EndingActor* EndActor = CreateActor<EndingActor>();
		EndActor->SetPos(TempPos + float4{TILESIZE.X * 10.0f, 0});
		TempPos = EndActor->GetPos();
		EndActor->InitAnimation("Npc" + std::to_string(1), NameText[i]);
	}
}

void EndingLevel::Update(float _Delta)
{
	if (true == SkipButtonCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect)
		&& true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		GameEngineWindow::MainWindow.WindowUpdateOff();
	}
}

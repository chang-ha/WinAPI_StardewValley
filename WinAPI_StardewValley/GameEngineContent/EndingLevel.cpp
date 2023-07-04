#define ACTORSPEED1 120.0f
#define ACTORSPEED2 105.0f

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
		Texture = ResourcesManager::GetInst().TextureCreate("BackBelow", { 1600, 900 });
		Texture->FillTexture(RGB(255, 0, 0));

		BackBelow = CreateActor<BackGround>(UpdateOrder::Map);
		BackBelow->GetRenderer()->SetTexture("BackBelow");
		BackBelow->SetPos(GlobalValue::WinScale.Half());
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
		FilePath.MoveChild("Resources\\Sounds\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BGM\\Ending.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Effect\\Dog_bark.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Effect\\Cat_Meow.wav"));
	}

	// Ending UI
	CategoryActor = CreateActor<PlayOver>();
	CategoryActor->GetRenderer()->SetText("ÀÌ¿ô", 40, "Sandoll ¹Ì»ý");
	CategoryActor->GetRenderer()->ChangeTextColor(RGB(255, 255, 0));
	CategoryActor->SetPos({GlobalValue::WinScale.hX(), GlobalValue::WinScale.Y * 0.85f});
	CategoryActor->On();

	PlayOver* SkipButton = CreateActor<PlayOver>();
	SkipButton->Init("UI_Skip.bmp");
	SkipButton->SetPos({ GlobalValue::WinScale.X - SkipButton->GetRenderScale().hX(), GlobalValue::WinScale.Y - SkipButton->GetRenderScale().hY()});

	SkipButtonCollision = SkipButton->CreateCollision(CollisionOrder::Button);
	SkipButtonCollision->SetCollisionScale(SkipButton->GetRenderScale());

	// Ending Actor

	// Neighbor
	float4 TempPos = { GlobalValue::WinScale.X, GlobalValue::WinScale.hY() };

	EndingActor* EndActor = nullptr;

	for (int i = 0; i < 30; i++)
	{
		EndActor = CreateActor<EndingActor>();
		EndActor->SetPos(TempPos + float4{TILESIZE.X * 3.0f, 0});
		TempPos = EndActor->GetPos();
		EndActor->InitAnimation("Npc" + std::to_string(i + 1));

		if (12 == i)
		{
			EndActor = CreateActor<EndingActor>();
			EndActor->SetPos(TempPos + float4{ TILESIZE.X * 3.0f, - TILESIZE.Y * 10.0f });
			EndActor->Init("Bulb");
		}
	}

	TempPos.X += TILESIZE.X * 15.0f;
	for (int i = 0; i < 4; i++)
	{
		EndActor = CreateActor<EndingActor>();
		EndActor->SetPos(TempPos + float4{TILESIZE.X * 3.0f, 0});
		TempPos = EndActor->GetPos();
		EndActor->InitAnimation("Npc" + std::to_string(i + 31), 0.1f);
	}

	// Creature
	Dog = CreateActor<EndingActor>();
	Dog->SetPos(TempPos + float4{ TILESIZE.X * 3.0f, TILESIZE.X * 4.0f });
	Dog->InitAnimation("Dog", 0.08f, ACTORSPEED1);

	TempPos.X += TILESIZE.X * 15.0f;
	TempPos.Y += TILESIZE.Y * 2.0f;
	std::vector<std::string> NameText;
	NameText.resize(13);
	NameText[0] = ("Èò ´ß");
	NameText[1] = ("°¥»ö ´ß");
	NameText[2] = ("ÆÄ¶õ ´ß");
	NameText[3] = ("°øÇã ´ß");
	NameText[4] = ("È²±Ý ´ß");
	NameText[5] = ("¿À¸®");
	NameText[6] = ("Åä³¢");
	NameText[7] = ("°ø·æ");
	NameText[8] = ("Èò ¼Ò");
	NameText[9] = ("¿°¼Ò");
	NameText[10] = ("µÅÁö");
	NameText[11] = ("¾ç");
	NameText[12] = ("Å¸Á¶");
	for (int i = 0; i < 13; i++)
	{
		EndActor = CreateActor<EndingActor>();
		EndActor->SetPos(TempPos + float4{TILESIZE.X * 15.0f, 0});
		TempPos = EndActor->GetPos();
		EndActor->InitAnimation("Animal" + std::to_string(i+1), NameText[i]);
	}

	Cat = CreateActor<EndingActor>();
	Cat->SetPos(TempPos + float4{ - TILESIZE.X * 10.0f, - TILESIZE.X * 6.0f });
	Cat->InitAnimation("Cat", 0.08f, ACTORSPEED1);

	EndActor = CreateActor<EndingActor>();
	EndActor->SetPos(TempPos + float4{ TILESIZE.X * 20.0f, TILESIZE.Y * 7.4f });
	EndActor->InitAnimation("Squirrel", 0.1f, ACTORSPEED1, 6);

	EndActor = CreateActor<EndingActor>();
	EndActor->SetPos(TempPos + float4{ TILESIZE.X * 33.0f, TILESIZE.Y * 7.4f });
	EndActor->InitAnimation("Rabbit1", 0.1f, ACTORSPEED1, 6);

	EndActor = CreateActor<EndingActor>();
	EndActor->SetPos(TempPos + float4{ TILESIZE.X * 38.0f, TILESIZE.Y * 7.4f });
	EndActor->InitAnimation("Rabbit2", 0.1f, ACTORSPEED1, 6);

	EndActor = CreateActor<EndingActor>();
	EndActor->SetPos(TempPos + float4{ TILESIZE.X * 57.0f, - TILESIZE.Y * 9.0f });
	EndActor->InitAnimation("Bird1", 0.1f, ACTORSPEED1, 4);

	EndActor = CreateActor<EndingActor>();
	EndActor->SetPos(TempPos + float4{ TILESIZE.X * 61.0f, -TILESIZE.Y * 8.0f });
	EndActor->InitAnimation("Bird1", 0.1f, ACTORSPEED1, 4);

	EndActor = CreateActor<EndingActor>();
	EndActor->SetPos(TempPos + float4{ TILESIZE.X * 67.0f, -TILESIZE.Y * 11.0f });
	EndActor->InitAnimation("Bird2", 0.1f, ACTORSPEED1, 4);

	EndActor = CreateActor<EndingActor>();
	EndActor->SetPos(TempPos + float4{ TILESIZE.X * 63.0f, -TILESIZE.Y * 11.0f });
	EndActor->InitAnimation("Bird3", 0.1f, ACTORSPEED1, 4);

	EndActor = CreateActor<EndingActor>();
	EndActor->SetPos(TempPos + float4{ TILESIZE.X * 65.0f, TILESIZE.Y * 8.4f });
	EndActor->InitAnimation("Frog1", 0.1f, ACTORSPEED2, 5);

	EndActor = CreateActor<EndingActor>();
	EndActor->SetPos(TempPos + float4{ TILESIZE.X * 70.0f, TILESIZE.Y * 8.4f });
	EndActor->InitAnimation("Frog2", 0.1f, ACTORSPEED2, 5);
}

void EndingLevel::Update(float _Delta)
{
	static bool BoolValue = true;
	static float OnTime = 0.0f;
	OnTime += _Delta;

	if (38.0f <= OnTime)
	{
		CategoryActor->Off();
		BoolValue = false;
	}
	else if (33.0f <= OnTime && true == BoolValue)
	{
		CategoryActor->On();
		CategoryActor->GetRenderer()->SetText("µ¿¹°", 40, "Sandoll ¹Ì»ý");
		CategoryActor->GetRenderer()->ChangeTextColor(RGB(255, 255, 255));
		BoolValue = false;
	}
	else if (32.0f <= OnTime)
	{
		BoolValue = true;
	}
	else if (5.0f <= OnTime && true == BoolValue)
	{
		CategoryActor->Off();
		BoolValue = false;
	}

	if (true == SkipButtonCollision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect)
		&& true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		GameEngineWindow::MainWindow.WindowUpdateOff();
	}

	if (0b11111111 == RValue && 0b00000000 == GValue)
	{
		RValueBool = true;
		GValueBool = true;
		BValueBool = false;
	}
	else if (0b11111111 == RValue && 0b11111111 == GValue)
	{
		RValueBool = false;
		GValueBool = true;
		BValueBool = false;
	}
	else if (0b11111111 == GValue && 0b00000000 == BValue)
	{
		RValueBool = false;
		GValueBool = true;
		BValueBool = true;
	}
	else if (0b11111111 == GValue && 0b11111111 == BValue)
	{
		RValueBool = false;
		GValueBool = false;
		BValueBool = true;
	}
	else if (0b11111111 == BValue && 0b00000000 == RValue)
	{
		RValueBool = true;
		GValueBool = false;
		BValueBool = true;
	}
	else if (0b11111111 == BValue && 0b11111111 == RValue)
	{
		RValueBool = true;
		GValueBool = false;
		BValueBool = false;
	}

	ColorValueUpdate(RValue, RValueBool);
	ColorValueUpdate(GValue, GValueBool);
	ColorValueUpdate(BValue, BValueBool);
	Texture->FillTexture(RValue + (GValue << 8) + (BValue << 16));
	BackBelow->GetRenderer()->SetTexture("BackBelow");

	static bool BoolValue2 = true;
	if (GlobalValue::WinScale.X + 30.0f>= Dog->GetPos().X && true == BoolValue2)
	{
		EffectPlayer = GameEngineSound::SoundPlay("Dog_bark.wav");
		BoolValue2 = false;
	}

	static bool BoolValue3 = true;
	if (GlobalValue::WinScale.X + 30.0f >= Cat->GetPos().X && true == BoolValue3)
	{
		EffectPlayer = GameEngineSound::SoundPlay("Cat_Meow.wav");
		BoolValue3 = false;
	}
}

void EndingLevel::ColorValueUpdate(unsigned char& _RGBValue, bool _BoolValue)
{
	if (true == _BoolValue && 0b11111111 != _RGBValue)
	{
		_RGBValue += 1;
	}
	else if (false == _BoolValue && 0b00000000 != _RGBValue)
	{
		_RGBValue -= 1;
	}
}


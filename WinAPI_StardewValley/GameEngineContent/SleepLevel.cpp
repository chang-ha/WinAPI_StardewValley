#define RENDERTIME 0.5f

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "SleepLevel.h"
#include "ContentsEnum.h"
#include "BackGround.h"
#include "PlayOver.h"
#include "ContentUIManager.h"

SleepLevel::SleepLevel()
{

}

SleepLevel::~SleepLevel()
{

}

void SleepLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
	ContentUIManager::MainUI->PlusDayValue();
	if (nullptr != ContentUIManager::MainUI->GetSellItem())
	{
		ContentUIManager::MainUI->SellCurItem();
	}
}
void SleepLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	ContentUIManager::MainUI->SleepMoneyRenderOff();
	ContentUIManager::MainUI->ResetTimeValue();
}

void SleepLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Ok_Button.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("UI\\Ok_Button.bmp"));
	}
	Back = CreateActor<BackGround>(UpdateOrder::Map);
	Back->Init("SleepTime.bmp", 1.25f);
	Back->SetPos(GlobalValue::WinScale.Half());

	PlayOver* OK_Button = CreateActor<PlayOver>();
	OK_Button->Init("Ok_Button.bmp");
	OK_Button->SetPos({GlobalValue::WinScale.X * 0.7f, GlobalValue::WinScale.Y * 0.9f });
	OK_Button->Renderer->SetRenderScaleToTexture();
	OK_Button_Collision = OK_Button->CreateCollision(CollisionOrder::Button);
	OK_Button_Collision->SetCollisionScale(TILESIZE * RENDERRATIO);
}

void SleepLevel::Update(float _Delta)
{
	static float PerTime = RENDERTIME;
	ContentUIManager::MoneyData* _MoneyData;
	if (true == ContentUIManager::MainUI->GetMoneyData(EtcMoney)->MoneyIsUpdate()
		&& true == ContentUIManager::MainUI->GetMoneyData(EtcMoney)->IsUpdateEnd()
		&& 0.0f > PerTime)
	{
		_MoneyData = ContentUIManager::MainUI->GetMoneyData(TotalMoney);
		_MoneyData->On();
		PerTime = RENDERTIME;
	}
	else if (true == ContentUIManager::MainUI->GetMoneyData(MiningMoney)->MoneyIsUpdate()
		&& true == ContentUIManager::MainUI->GetMoneyData(MiningMoney)->IsUpdateEnd()
		&& 0.0f > PerTime)
	{
		_MoneyData = ContentUIManager::MainUI->GetMoneyData(EtcMoney);
		_MoneyData->On();
		PerTime = RENDERTIME;
		EffectPlayer = GameEngineSound::SoundPlay("cancel.wav");
	}
	else if (true == ContentUIManager::MainUI->GetMoneyData(FishingMoney)->MoneyIsUpdate()
		&& true == ContentUIManager::MainUI->GetMoneyData(FishingMoney)->IsUpdateEnd()
		&& 0.0f > PerTime)
	{
		_MoneyData = ContentUIManager::MainUI->GetMoneyData(MiningMoney);
		_MoneyData->On();
		PerTime = RENDERTIME;
		EffectPlayer = GameEngineSound::SoundPlay("cancel.wav");
	}
	else if (true == ContentUIManager::MainUI->GetMoneyData(ResourcesMoney)->MoneyIsUpdate()
		&& true == ContentUIManager::MainUI->GetMoneyData(ResourcesMoney)->IsUpdateEnd()
		&& 0.0f > PerTime)
	{
		_MoneyData = ContentUIManager::MainUI->GetMoneyData(FishingMoney);
		_MoneyData->On();
		PerTime = RENDERTIME;
		EffectPlayer = GameEngineSound::SoundPlay("cancel.wav");
	}
	else if (true == ContentUIManager::MainUI->GetMoneyData(CropsMoney)->MoneyIsUpdate()
		&& true == ContentUIManager::MainUI->GetMoneyData(CropsMoney)->IsUpdateEnd()
		&& 0.0f > PerTime)
	{
		_MoneyData = ContentUIManager::MainUI->GetMoneyData(ResourcesMoney);
		_MoneyData->On();
		PerTime = RENDERTIME;
		EffectPlayer = GameEngineSound::SoundPlay("cancel.wav");
	}
	else if (false == ContentUIManager::MainUI->GetMoneyData(CropsMoney)->MoneyIsUpdate()
		&& 0.0f > PerTime)
	{
		_MoneyData = ContentUIManager::MainUI->GetMoneyData(CropsMoney);
		_MoneyData->On();
		PerTime = RENDERTIME;
		EffectPlayer = GameEngineSound::SoundPlay("cancel.wav");
	}

	if (true == ContentUIManager::MainUI->GetMoneyData(EtcMoney)->MoneyIsUpdate() 
		&& true == ContentUIManager::MainUI->GetMoneyData(TotalMoney)->IsUpdateEnd())
	{
		if (true == OK_Button_Collision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect)
			&& true == GameEngineInput::IsDown(VK_LBUTTON))
		{
			_MoneyData = ContentUIManager::MainUI->GetMoneyData(TotalMoney);
			ContentUIManager::MainUI->PlusPlayerMoney(_MoneyData->GetCurMoney());
			GameEngineCore::ChangeLevel("FarmHouse");
		}
	}
	PerTime -= _Delta;
}
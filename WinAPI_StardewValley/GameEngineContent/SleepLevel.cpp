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
}
void SleepLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
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
	OK_Button->SetPos(GlobalValue::WinScale.Half());
	OK_Button->Renderer->SetRenderScaleToTexture();
	OK_Button_Collision = OK_Button->CreateCollision(CollisionOrder::Button);
	OK_Button_Collision->SetCollisionScale(TILESIZE * RENDERRATIO);
}

void SleepLevel::Update(float _Delta)
{
	if (true == OK_Button_Collision->CollisionCheck(ContentMouse::MainMouse->GetMouseCollision(), CollisionType::Rect, CollisionType::Rect)
		&& true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		GameEngineCore::ChangeLevel("FarmHouse");
	}
}
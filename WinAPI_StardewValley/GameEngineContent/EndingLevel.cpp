#include "EndingLevel.h"
#include "ContentsEnum.h"
#include "BackGround.h"

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
		Back->Init("EndCredit.bmp", RENDERRATIO);
		Back->SetPos(GetRenderScale().Half());
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
}

void EndingLevel::Update(float _Delta)
{

}

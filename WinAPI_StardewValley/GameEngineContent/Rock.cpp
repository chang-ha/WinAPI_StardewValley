#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Rock.h"
#include "ContentsEnum.h"
#include "ContentItem.h"
#include "GlobalValue.h"

Rock::Rock()
{

}

Rock::~Rock()
{

}

void Rock::Init(const std::string& _FileName)
{
	ContentResources::Init(_FileName);
	if (nullptr == GameEngineSound::FindSound("rock.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("rock.wav"));
	}
}
void Rock::Start()
{

}
void Rock::Update(float _Delta)
{
	static float PerTime = 1.0f;
	if (true == Collision->Collision(CollisionOrder::Axe, _CollisionResult, CollisionType::Rect, CollisionType::Rect)/* && 0.0f > PerTime*/)
	{
		EffectPlayer = GameEngineSound::SoundPlay("rock.wav");

		GameEngineLevel* CurLevel = GetLevel();
		for (int x = 0; x < ItemCount; x++)
		{
			ContentItem* Item = CurLevel->CreateActor<ContentItem>(UpdateOrder::Inventory);
			Item->Init("Rock.bmp", ItemType::Resources);
			Item->SetPos(GetPos() + float4{ x * RENDERRATIO * 8, 0 });
		}
		Death();
	}
	PerTime -= _Delta;
}
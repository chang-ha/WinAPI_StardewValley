#define RUNSPEED1 0.08f
#define RUNSPEED2 0.1f
#define TOOL1SPEED 0.07f
#define TOOL1LASTANI 0.1f
#define TOOL2SPEED 0.07f
#define TOOL2LASTANI 0.6f
#define TOOL3SPEED 0.05f
#define HARVESTSPEED 0.06f
#define WATERSPEED 0.1f

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/TileMap.h>

#include "Player.h"
#include "ContentLevel.h"
#include "ContentsEnum.h"
#include "ContentUIManager.h"
#include "ContentItem.h"
#include "ContentInventory.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{
	
}

Player::~Player()
{

}

void Player::LevelStart()
{
}

void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Up_Player_Body.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Player\\");

		// Body Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Body", FilePath.PlusFilePath("Player_body\\Up_Player_Body.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Body", FilePath.PlusFilePath("Player_body\\Down_Player_Body.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Body", FilePath.PlusFilePath("Player_body\\Right_Player_Body.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Body", FilePath.PlusFilePath("Player_body\\Left_Player_Body.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_body_Tool1", FilePath.PlusFilePath("Player_body\\Up_Player_body_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_body_Tool1", FilePath.PlusFilePath("Player_body\\Down_Player_body_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_body_Tool1", FilePath.PlusFilePath("Player_body\\Right_Player_body_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_body_Tool1", FilePath.PlusFilePath("Player_body\\Left_Player_body_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_body_Tool2", FilePath.PlusFilePath("Player_body\\Down_Player_body_Tool2.bmp"), 3, 1);		
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_body_Tool2", FilePath.PlusFilePath("Player_body\\Right_Player_body_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_body_Tool2", FilePath.PlusFilePath("Player_body\\Left_Player_body_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_body_Tool2", FilePath.PlusFilePath("Player_body\\Up_Player_body_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_body_Harvest", FilePath.PlusFilePath("Player_body\\Down_Player_body_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_body_Harvest", FilePath.PlusFilePath("Player_body\\Right_Player_body_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_body_Harvest", FilePath.PlusFilePath("Player_body\\Left_Player_body_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_body_Harvest", FilePath.PlusFilePath("Player_body\\Up_Player_body_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_body_Tool3", FilePath.PlusFilePath("Player_body\\Up_Player_body_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_body_Tool3", FilePath.PlusFilePath("Player_body\\Down_Player_body_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_body_Tool3", FilePath.PlusFilePath("Player_body\\Right_Player_body_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_body_Tool3", FilePath.PlusFilePath("Player_body\\Left_Player_body_Tool3.bmp"), 6, 1);

		// Pants Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Pants", FilePath.PlusFilePath("Player_pants\\Up_Player_pants1.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Pants", FilePath.PlusFilePath("Player_pants\\Down_Player_pants1.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Pants", FilePath.PlusFilePath("Player_pants\\Right_Player_pants1.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Pants", FilePath.PlusFilePath("Player_pants\\Left_Player_pants1.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Pants_Tool1", FilePath.PlusFilePath("Player_pants\\Down_Player_pants1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Pants_Tool1", FilePath.PlusFilePath("Player_pants\\Right_Player_pants1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Pants_Tool1", FilePath.PlusFilePath("Player_pants\\Left_Player_pants1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Pants_Tool1", FilePath.PlusFilePath("Player_pants\\Up_Player_pants1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Pants_Tool2", FilePath.PlusFilePath("Player_pants\\Down_Player_pants1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Pants_Tool2", FilePath.PlusFilePath("Player_pants\\Right_Player_pants1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Pants_Tool2", FilePath.PlusFilePath("Player_pants\\Left_Player_pants1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Pants_Tool2", FilePath.PlusFilePath("Player_pants\\Up_Player_pants1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Pants_Harvest", FilePath.PlusFilePath("Player_pants\\Down_Player_pants1_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Pants_Harvest", FilePath.PlusFilePath("Player_pants\\Right_Player_pants1_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Pants_Harvest", FilePath.PlusFilePath("Player_pants\\Left_Player_pants1_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Pants_Harvest", FilePath.PlusFilePath("Player_pants\\Up_Player_pants1_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Pants_Tool3", FilePath.PlusFilePath("Player_pants\\Up_Player_pants1_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Pants_Tool3", FilePath.PlusFilePath("Player_pants\\Down_Player_pants1_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Pants_Tool3", FilePath.PlusFilePath("Player_pants\\Right_Player_pants1_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Pants_Tool3", FilePath.PlusFilePath("Player_pants\\Left_Player_pants1_Tool3.bmp"), 6, 1);

		// Shirt Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Shirt", FilePath.PlusFilePath("Player_shirt\\Up_Player_shirt1.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Shirt", FilePath.PlusFilePath("Player_shirt\\Down_Player_shirt1.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Shirt", FilePath.PlusFilePath("Player_shirt\\Right_Player_shirt1.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Shirt", FilePath.PlusFilePath("Player_shirt\\Left_Player_shirt1.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Shirt_Tool1", FilePath.PlusFilePath("Player_shirt\\Down_Player_shirt1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Shirt_Tool1", FilePath.PlusFilePath("Player_shirt\\Right_Player_shirt1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Shirt_Tool1", FilePath.PlusFilePath("Player_shirt\\Left_Player_shirt1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Shirt_Tool1", FilePath.PlusFilePath("Player_shirt\\Up_Player_shirt1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Shirt_Tool2", FilePath.PlusFilePath("Player_shirt\\Down_Player_shirt1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Shirt_Tool2", FilePath.PlusFilePath("Player_shirt\\Right_Player_shirt1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Shirt_Tool2", FilePath.PlusFilePath("Player_shirt\\Left_Player_shirt1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Shirt_Tool2", FilePath.PlusFilePath("Player_shirt\\Up_Player_shirt1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Shirt_Harvest", FilePath.PlusFilePath("Player_shirt\\Down_Player_shirt1_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Shirt_Harvest", FilePath.PlusFilePath("Player_shirt\\Right_Player_shirt1_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Shirt_Harvest", FilePath.PlusFilePath("Player_shirt\\Left_Player_shirt1_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Shirt_Harvest", FilePath.PlusFilePath("Player_shirt\\Up_Player_shirt1_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_Shirt_Tool3", FilePath.PlusFilePath("Player_shirt\\Up_Player_shirt1_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_Shirt_Tool3", FilePath.PlusFilePath("Player_shirt\\Down_Player_shirt1_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_Shirt_Tool3", FilePath.PlusFilePath("Player_shirt\\Right_Player_shirt1_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_Shirt_Tool3", FilePath.PlusFilePath("Player_shirt\\Left_Player_shirt1_Tool3.bmp"), 6, 1);

		// Arm Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_arm", FilePath.PlusFilePath("Player_arm\\Up_Player_arm.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_arm", FilePath.PlusFilePath("Player_arm\\Down_Player_arm.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_arm", FilePath.PlusFilePath("Player_arm\\Right_Player_arm.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_arm", FilePath.PlusFilePath("Player_arm\\Left_Player_arm.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_arm_Tool1", FilePath.PlusFilePath("Player_arm\\Down_Player_arm_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_arm_Tool1", FilePath.PlusFilePath("Player_arm\\Right_Player_arm_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_arm_Tool1", FilePath.PlusFilePath("Player_arm\\Left_Player_arm_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_arm_Tool1", FilePath.PlusFilePath("Player_arm\\Up_Player_arm_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_arm_Tool2", FilePath.PlusFilePath("Player_arm\\Down_Player_arm_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_arm_Tool2", FilePath.PlusFilePath("Player_arm\\Right_Player_arm_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_arm_Tool2", FilePath.PlusFilePath("Player_arm\\Left_Player_arm_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_arm_Tool2", FilePath.PlusFilePath("Player_arm\\Up_Player_arm_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_arm_Harvest", FilePath.PlusFilePath("Player_arm\\Down_Player_arm_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_arm_Harvest", FilePath.PlusFilePath("Player_arm\\Right_Player_arm_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_arm_Harvest", FilePath.PlusFilePath("Player_arm\\Left_Player_arm_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_arm_Harvest", FilePath.PlusFilePath("Player_arm\\Up_Player_arm_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_arm_Tool3", FilePath.PlusFilePath("Player_arm\\Up_Player_arm_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_arm_Tool3", FilePath.PlusFilePath("Player_arm\\Down_Player_arm_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_arm_Tool3", FilePath.PlusFilePath("Player_arm\\Right_Player_arm_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_arm_Tool3", FilePath.PlusFilePath("Player_arm\\Left_Player_arm_Tool3.bmp"), 6, 1);

		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_arm_Item", FilePath.PlusFilePath("Player_arm\\Up_Player_arm_Item.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_arm_Item", FilePath.PlusFilePath("Player_arm\\Down_Player_arm_Item.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_arm_Item", FilePath.PlusFilePath("Player_arm\\Right_Player_arm_Item.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_arm_Item", FilePath.PlusFilePath("Player_arm\\Left_Player_arm_Item.bmp"), 7, 1);


		// Hair Animation
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_hair", FilePath.PlusFilePath("Player_hair\\Up_Player_hair1.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_hair", FilePath.PlusFilePath("Player_hair\\Down_Player_hair1.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_hair", FilePath.PlusFilePath("Player_hair\\Right_Player_hair1.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_hair", FilePath.PlusFilePath("Player_hair\\Left_Player_hair1.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_hair_Tool1", FilePath.PlusFilePath("Player_hair\\Down_Player_hair1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_hair_Tool1", FilePath.PlusFilePath("Player_hair\\Right_Player_hair1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_hair_Tool1", FilePath.PlusFilePath("Player_hair\\Left_Player_hair1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_hair_Tool1", FilePath.PlusFilePath("Player_hair\\Up_Player_hair1_Tool1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_hair_Tool2", FilePath.PlusFilePath("Player_hair\\Down_Player_hair1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_hair_Tool2", FilePath.PlusFilePath("Player_hair\\Right_Player_hair1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_hair_Tool2", FilePath.PlusFilePath("Player_hair\\Left_Player_hair1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_hair_Tool2", FilePath.PlusFilePath("Player_hair\\Up_Player_hair1_Tool2.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_hair_Harvest", FilePath.PlusFilePath("Player_hair\\Down_Player_hair1_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_hair_Harvest", FilePath.PlusFilePath("Player_hair\\Right_Player_hair1_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_hair_Harvest", FilePath.PlusFilePath("Player_hair\\Left_Player_hair1_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_hair_Harvest", FilePath.PlusFilePath("Player_hair\\Up_Player_hair1_Harvest.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Player_hair_Tool3", FilePath.PlusFilePath("Player_hair\\Up_Player_hair1_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Player_hair_Tool3", FilePath.PlusFilePath("Player_hair\\Down_Player_hair1_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Player_hair_Tool3", FilePath.PlusFilePath("Player_hair\\Right_Player_hair1_Tool3.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Player_hair_Tool3", FilePath.PlusFilePath("Player_hair\\Left_Player_hair1_Tool3.bmp"), 6, 1);

		ResourcesManager::GetInst().CreateSpriteSheet("Shadow.bmp", FilePath.PlusFilePath("Shadow.bmp"), 1, 1);

		// Tool Sprite
		//Hoe
		GameEngineSprite* Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet("Right_Hoe.bmp", FilePath.PlusFilePath("Player_tool\\Right_Hoe.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Right_Hoe_Mask.bmp"));
		Sprite0->SetMaskTexture("Right_Hoe_Mask.bmp");

		Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet("Left_Hoe.bmp", FilePath.PlusFilePath("Player_tool\\Left_Hoe.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Left_Hoe_Mask.bmp"));
		Sprite0->SetMaskTexture("Left_Hoe_Mask.bmp");

		Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet("Down_Hoe.bmp", FilePath.PlusFilePath("Player_tool\\Down_Hoe.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Down_Hoe_Mask.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Down2_Hoe.bmp"));
		Sprite0->SetMaskTexture("Down_Hoe_Mask.bmp");

		ResourcesManager::GetInst().CreateSpriteSheet("Up_Hoe.bmp", FilePath.PlusFilePath("Player_tool\\Up_Hoe.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Up2_Hoe.bmp"));

		// Axe
		Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet("Right_Axe.bmp", FilePath.PlusFilePath("Player_tool\\Right_Axe.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Right_Axe_Mask.bmp"));
		Sprite0->SetMaskTexture("Right_Axe_Mask.bmp");

		Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet("Left_Axe.bmp", FilePath.PlusFilePath("Player_tool\\Left_Axe.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Left_Axe_Mask.bmp"));
		Sprite0->SetMaskTexture("Left_Axe_Mask.bmp");

		Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet("Down_Axe.bmp", FilePath.PlusFilePath("Player_tool\\Down_Axe.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Down_Axe_Mask.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Down2_Axe.bmp"));
		Sprite0->SetMaskTexture("Down_Axe_Mask.bmp");

		ResourcesManager::GetInst().CreateSpriteSheet("Up_Axe.bmp", FilePath.PlusFilePath("Player_tool\\Up_Axe.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Up2_Axe.bmp"));

		// PickAxe
		Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet("Right_PickAxe.bmp", FilePath.PlusFilePath("Player_tool\\Right_PickAxe.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Right_PickAxe_Mask.bmp"));
		Sprite0->SetMaskTexture("Right_PickAxe_Mask.bmp");

		Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet("Left_PickAxe.bmp", FilePath.PlusFilePath("Player_tool\\Left_PickAxe.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Left_PickAxe_Mask.bmp"));
		Sprite0->SetMaskTexture("Left_PickAxe_Mask.bmp");

		Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet("Down_PickAxe.bmp", FilePath.PlusFilePath("Player_tool\\Down_PickAxe.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Down_PickAxe_Mask.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Down2_PickAxe.bmp"));
		Sprite0->SetMaskTexture("Down_PickAxe_Mask.bmp");

		ResourcesManager::GetInst().CreateSpriteSheet("Up_PickAxe.bmp", FilePath.PlusFilePath("Player_tool\\Up_PickAxe.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Up2_PickAxe.bmp"));

		// WateringCan
		Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet("Right_WateringCan.bmp", FilePath.PlusFilePath("Player_tool\\Right_WateringCan.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Right2_WateringCan.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Right_WateringCan_Mask.bmp"));
		Sprite0->SetMaskTexture("Right_WateringCan_Mask.bmp");

		Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet("Left_WateringCan.bmp", FilePath.PlusFilePath("Player_tool\\Left_WateringCan.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Left2_WateringCan.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Left_WateringCan_Mask.bmp"));
		Sprite0->SetMaskTexture("Left_WateringCan_Mask.bmp");

		ResourcesManager::GetInst().CreateSpriteSheet("Down_WateringCan.bmp", FilePath.PlusFilePath("Player_tool\\Down_WateringCan.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Down2_WateringCan.bmp"));

		ResourcesManager::GetInst().CreateSpriteSheet("Up_WateringCan.bmp", FilePath.PlusFilePath("Player_tool\\Up_WateringCan.bmp"), 1, 1);

		// Sickle
		Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet("Sickle.bmp", FilePath.PlusFilePath("Player_tool\\Tool_Sickle.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Tool_Sickle_Mask.bmp"));
		Sprite0->SetMaskTexture("Tool_Sickle_Mask.bmp");

		Sprite0 = ResourcesManager::GetInst().CreateSpriteSheet("Left_Sickle.bmp", FilePath.PlusFilePath("Player_tool\\Left_Tool_Sickle.bmp"), 1, 1);
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Player_tool\\Left_Tool_Sickle_Mask.bmp"));
		Sprite0->SetMaskTexture("Left_Tool_Sickle_Mask.bmp");

		// Water
		ResourcesManager::GetInst().CreateSpriteSheet("WaterAnimation", FilePath.PlusFilePath("Player_tool\\WaterAnimation.bmp"), 10, 1);
	}

	// Sound Load
	if (nullptr == GameEngineSound::FindSound("grassyStep.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sounds\\Effect\\");
		
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("grassyStep.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("woodyStep.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("sandyStep.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("stoneStep.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("thudStep.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("wateringcan.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("swipe.wav"));
	}

	// Player Renderer 
	ShadowRenderer = CreateRenderer(RenderOrder::Shadow);
	WaterRenderer = CreateRenderer(RenderOrder::PlayBelow);
	WaterRenderer->Off();

	BodyRenderer = CreateRenderer(RenderOrder::Play);
	BodyRenderer->SetScaleRatio(RENDERRATIO);

	PantsRenderer = CreateRenderer(RenderOrder::Play);
	PantsRenderer->SetScaleRatio(RENDERRATIO);

	ShirtRenderer = CreateRenderer(RenderOrder::Play);
	ShirtRenderer->SetScaleRatio(RENDERRATIO);
	
	ArmRenderer = CreateRenderer(RenderOrder::Play);
	ArmRenderer->SetScaleRatio(RENDERRATIO);
	ArmRenderer->SetYPivot(5 *RENDERRATIO);

	HairRenderer = CreateRenderer(RenderOrder::Play);
	HairRenderer->SetScaleRatio(RENDERRATIO);

	ToolRenderer = CreateRenderer(RenderOrder::PlayOver);
	ToolRenderer->SetRenderScale(float4{16, 50} * RENDERRATIO);
	ToolRenderer->Off();

	CurItemRenderer = CreateRenderer(RenderOrder::Play);
	CurItemRenderer->SetRenderScale(TILESIZE * RENDERRATIO);
	CurItemRenderer->SetRenderPos(float4{0, -15} * RENDERRATIO);
	CurItemRenderer->SetYPivot(16 * RENDERRATIO);
	CurItemRenderer->Off();
	// Shadow
	ShadowRenderer->SetAlpha(120);
	ShadowRenderer->CreateAnimation("Idle", "Shadow.bmp", 0, 0);
	ShadowRenderer->ChangeAnimation("Idle");
	ShadowRenderer->SetScaleRatio(RENDERRATIO);
	ShadowRenderer->SetRenderPos(float4{ 0, 14 } *RENDERRATIO);

	// Body
	{
		// Up
		{
			BodyRenderer->CreateAnimation("Up_Idle", "Up_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Up_Run", "Up_Player_Body", 1, 8, RUNSPEED1);
			BodyRenderer->CreateAnimation("Up_Tool1", "Up_Player_body_Tool1", 0, 4, TOOL1SPEED, false);
			BodyRenderer->CreateAnimation("Up_Tool2", "Up_Player_body_Tool2", 0, 2, TOOL2SPEED, false);
			BodyRenderer->FindAnimation("Up_Tool1")->Inters[4] = TOOL1LASTANI;
			BodyRenderer->FindAnimation("Up_Tool2")->Inters[2] = TOOL2LASTANI;
			BodyRenderer->CreateAnimation("Up_Harvest", "Up_Player_body_Harvest", 0, 3, HARVESTSPEED, false);
			BodyRenderer->CreateAnimation("Up_Tool3", "Up_Player_body_Tool3", 0, 5, TOOL3SPEED, false);
		}

		// Down
		{
			BodyRenderer->CreateAnimation("Down_Idle", "Down_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Down_Run", "Down_Player_Body", 1, 8, RUNSPEED1);
			BodyRenderer->CreateAnimation("Down_Tool1", "Down_Player_body_Tool1", 0, 4, TOOL1SPEED, false);
			BodyRenderer->CreateAnimation("Down_Tool2", "Down_Player_body_Tool2", 0, 2, TOOL2SPEED, false);
			BodyRenderer->FindAnimation("Down_Tool1")->Inters[4] = TOOL1LASTANI;
			BodyRenderer->FindAnimation("Down_Tool2")->Inters[2] = TOOL2LASTANI;
			BodyRenderer->CreateAnimation("Down_Harvest", "Down_Player_body_Harvest", 0, 3, HARVESTSPEED, false);
			BodyRenderer->CreateAnimation("Down_OpenBox", "Down_Player_body_Harvest", 3, 3, 5.0f, false);
			BodyRenderer->CreateAnimation("Down_Tool3", "Down_Player_body_Tool3", 0, 5, TOOL3SPEED, false);
		}
		
		// Right
		{
			BodyRenderer->CreateAnimation("Right_Idle", "Right_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Right_Run", "Right_Player_Body", 1, 6, RUNSPEED2);
			BodyRenderer->CreateAnimation("Right_Tool1", "Right_Player_body_Tool1", 0, 4, TOOL1SPEED, false);
			BodyRenderer->CreateAnimation("Right_Tool2", "Right_Player_body_Tool2", 0, 2, TOOL2SPEED, false);
			BodyRenderer->FindAnimation("Right_Tool1")->Inters[4] = TOOL1LASTANI;
			BodyRenderer->FindAnimation("Right_Tool2")->Inters[2] = TOOL2LASTANI;
			BodyRenderer->CreateAnimation("Right_Harvest", "Right_Player_body_Harvest", 0, 3, HARVESTSPEED, false);
			BodyRenderer->CreateAnimation("Right_Tool3", "Right_Player_body_Tool3", 0, 5, TOOL3SPEED, false);
		}
		
		// Left
		{
			BodyRenderer->CreateAnimation("Left_Idle", "Left_Player_Body", 0, 0);
			BodyRenderer->CreateAnimation("Left_Run", "Left_Player_Body", 1, 6, RUNSPEED2);
			BodyRenderer->CreateAnimation("Left_Tool1", "Left_Player_body_Tool1", 0, 4, TOOL1SPEED, false);
			BodyRenderer->CreateAnimation("Left_Tool2", "Left_Player_body_Tool2", 0, 2, TOOL2SPEED, false);
			BodyRenderer->FindAnimation("Left_Tool1")->Inters[4] = TOOL1LASTANI;
			BodyRenderer->FindAnimation("Left_Tool2")->Inters[2] = TOOL2LASTANI;
			BodyRenderer->CreateAnimation("Left_Harvest", "Left_Player_body_Harvest", 0, 3, HARVESTSPEED, false);
			BodyRenderer->CreateAnimation("Left_Tool3", "Left_Player_body_Tool3", 0, 5, TOOL3SPEED, false);
		}
	}

	// Pants
	{
		//Up
		{
			PantsRenderer->CreateAnimation("Up_Idle", "Up_Player_Pants", 0, 0);
			PantsRenderer->CreateAnimation("Up_Run", "Up_Player_Pants", 1, 8, RUNSPEED1);
			PantsRenderer->CreateAnimation("Up_Tool1", "Up_Player_Pants_Tool1", 0, 4, TOOL1SPEED, false);
			PantsRenderer->CreateAnimation("Up_Tool2", "Up_Player_Pants_Tool2", 0, 2, TOOL2SPEED, false);
			PantsRenderer->FindAnimation("Up_Tool1")->Inters[4] = TOOL1LASTANI;
			PantsRenderer->FindAnimation("Up_Tool2")->Inters[2] = TOOL2LASTANI;
			PantsRenderer->CreateAnimation("Up_Harvest", "Up_Player_Pants_Harvest", 0, 3, HARVESTSPEED, false);
			PantsRenderer->CreateAnimation("Up_Tool3", "Up_Player_Pants_Tool3", 0, 5, TOOL3SPEED, false);
		}

		//Down
		{
			PantsRenderer->CreateAnimation("Down_Idle", "Down_Player_Pants", 0, 0);
			PantsRenderer->CreateAnimation("Down_Run", "Down_Player_Pants", 1, 8, RUNSPEED1);
			PantsRenderer->CreateAnimation("Down_Tool1", "Down_Player_Pants_Tool1", 0, 4, TOOL1SPEED, false);
			PantsRenderer->CreateAnimation("Down_Tool2", "Down_Player_Pants_Tool2", 0, 2, TOOL2SPEED, false);
			PantsRenderer->FindAnimation("Down_Tool1")->Inters[4] = TOOL1LASTANI;
			PantsRenderer->FindAnimation("Down_Tool2")->Inters[2] = TOOL2LASTANI;
			PantsRenderer->CreateAnimation("Down_Harvest", "Down_Player_Pants_Harvest", 0, 3, HARVESTSPEED, false);
			PantsRenderer->CreateAnimation("Down_OpenBox", "Down_Player_Pants_Harvest", 3, 3, 5.0f, false);
			PantsRenderer->CreateAnimation("Down_Tool3", "Down_Player_Pants_Tool3", 0, 5, TOOL3SPEED, false);
		}

		//Right
		{
			PantsRenderer->CreateAnimation("Right_Idle", "Right_Player_Pants", 0, 0);
			PantsRenderer->CreateAnimation("Right_Run", "Right_Player_Pants", 1, 6, RUNSPEED2);
			PantsRenderer->CreateAnimation("Right_Tool1", "Right_Player_Pants_Tool1", 0, 4, TOOL1SPEED, false);
			PantsRenderer->CreateAnimation("Right_Tool2", "Right_Player_Pants_Tool2", 0, 2, TOOL2SPEED, false);
			PantsRenderer->FindAnimation("Right_Tool1")->Inters[4] = TOOL1LASTANI;
			PantsRenderer->FindAnimation("Right_Tool2")->Inters[2] = TOOL2LASTANI;
			PantsRenderer->CreateAnimation("Right_Harvest", "Right_Player_Pants_Harvest", 0, 3, HARVESTSPEED, false);
			PantsRenderer->CreateAnimation("Right_Tool3", "Right_Player_Pants_Tool3", 0, 5, TOOL3SPEED, false);
		}

		//Left
		{
			PantsRenderer->CreateAnimation("Left_Idle", "Left_Player_Pants", 0, 0);
			PantsRenderer->CreateAnimation("Left_Run", "Left_Player_Pants", 1, 6, RUNSPEED2);
			PantsRenderer->CreateAnimation("Left_Tool1", "Left_Player_Pants_Tool1", 0, 4, TOOL1SPEED, false);
			PantsRenderer->CreateAnimation("Left_Tool2", "Left_Player_Pants_Tool2", 0, 2, TOOL2SPEED, false);
			PantsRenderer->FindAnimation("Left_Tool1")->Inters[4] = TOOL1LASTANI;
			PantsRenderer->FindAnimation("Left_Tool2")->Inters[2] = TOOL2LASTANI;
			PantsRenderer->CreateAnimation("Left_Harvest", "Left_Player_Pants_Harvest", 0, 3, HARVESTSPEED, false);
			PantsRenderer->CreateAnimation("Left_Tool3", "Left_Player_Pants_Tool3", 0, 5, TOOL3SPEED, false);
		}
	}

	// Shirt
	{
		//Up
		{
			ShirtRenderer->CreateAnimation("Up_Idle", "Up_Player_Shirt", 0, 0);
			ShirtRenderer->CreateAnimation("Up_Run", "Up_Player_Shirt", 1, 8, RUNSPEED1);
			ShirtRenderer->CreateAnimation("Up_Tool1", "Up_Player_Shirt_Tool1", 0, 4, TOOL1SPEED, false);
			ShirtRenderer->CreateAnimation("Up_Tool2", "Up_Player_Shirt_Tool2", 0, 2, TOOL2SPEED, false);
			ShirtRenderer->FindAnimation("Up_Tool1")->Inters[4] = TOOL1LASTANI;
			ShirtRenderer->FindAnimation("Up_Tool2")->Inters[2] = TOOL2LASTANI;
			ShirtRenderer->CreateAnimation("Up_Harvest", "Up_Player_Shirt_Harvest", 0, 3, HARVESTSPEED, false);
			ShirtRenderer->CreateAnimation("Up_Tool3", "Up_Player_Shirt_Tool3", 0, 5, TOOL3SPEED, false);
		}

		//Down
		{
			ShirtRenderer->CreateAnimation("Down_Idle", "Down_Player_Shirt", 0, 0);
			ShirtRenderer->CreateAnimation("Down_Run", "Down_Player_Shirt", 1, 8, RUNSPEED1);
			ShirtRenderer->CreateAnimation("Down_Tool1", "Down_Player_Shirt_Tool1", 0, 4, TOOL1SPEED, false);
			ShirtRenderer->CreateAnimation("Down_Tool2", "Down_Player_Shirt_Tool2", 0, 2, TOOL2SPEED, false);
			ShirtRenderer->FindAnimation("Down_Tool1")->Inters[4] = TOOL1LASTANI;
			ShirtRenderer->FindAnimation("Down_Tool2")->Inters[2] = TOOL2LASTANI;
			ShirtRenderer->CreateAnimation("Down_Harvest", "Down_Player_Shirt_Harvest", 0, 3, HARVESTSPEED, false);
			ShirtRenderer->CreateAnimation("Down_OpenBox", "Down_Player_Shirt_Harvest", 3, 3, 5.0f, false);
			ShirtRenderer->CreateAnimation("Down_Tool3", "Down_Player_Shirt_Tool3", 0, 5, TOOL3SPEED, false);
		}

		//Right
		{
			ShirtRenderer->CreateAnimation("Right_Idle", "Right_Player_Shirt", 0, 0);
			ShirtRenderer->CreateAnimation("Right_Run", "Right_Player_Shirt", 1, 6, RUNSPEED2);
			ShirtRenderer->CreateAnimation("Right_Tool1", "Right_Player_Shirt_Tool1", 0, 4, TOOL1SPEED, false);
			ShirtRenderer->CreateAnimation("Right_Tool2", "Right_Player_Shirt_Tool2", 0, 2, TOOL2SPEED, false);
			ShirtRenderer->FindAnimation("Right_Tool1")->Inters[4] = TOOL1LASTANI;
			ShirtRenderer->FindAnimation("Right_Tool2")->Inters[2] = TOOL2LASTANI;
			ShirtRenderer->CreateAnimation("Right_Harvest", "Right_Player_Shirt_Harvest", 0, 3, HARVESTSPEED, false);
			ShirtRenderer->CreateAnimation("Right_Tool3", "Right_Player_Shirt_Tool3", 0, 5, TOOL3SPEED, false);
		}

		//Left
		{
			ShirtRenderer->CreateAnimation("Left_Idle", "Left_Player_Shirt", 0, 0);
			ShirtRenderer->CreateAnimation("Left_Run", "Left_Player_Shirt", 1, 6, RUNSPEED2);
			ShirtRenderer->CreateAnimation("Left_Tool1", "Left_Player_Shirt_Tool1", 0, 4, TOOL1SPEED, false);
			ShirtRenderer->CreateAnimation("Left_Tool2", "Left_Player_Shirt_Tool2", 0, 2, TOOL2SPEED, false);
			ShirtRenderer->FindAnimation("Left_Tool1")->Inters[4] = TOOL1LASTANI;
			ShirtRenderer->FindAnimation("Left_Tool2")->Inters[2] = TOOL2LASTANI;
			ShirtRenderer->CreateAnimation("Left_Harvest", "Left_Player_Shirt_Harvest", 0, 3, HARVESTSPEED, false);
			ShirtRenderer->CreateAnimation("Left_Tool3", "Left_Player_Shirt_Tool3", 0, 5, TOOL3SPEED, false);
		}
	}
	
	// Arm
	{
		// Up
		{
			ArmRenderer->CreateAnimation("Up_Idle", "Up_Player_arm", 0, 0);
			ArmRenderer->CreateAnimation("Up_Run", "Up_Player_arm", 1, 8, RUNSPEED1);
			ArmRenderer->CreateAnimation("Up_Tool1", "Up_Player_arm_Tool1", 0, 4, TOOL1SPEED, false);
			ArmRenderer->CreateAnimation("Up_Tool2", "Up_Player_arm_Tool2", 0, 2, TOOL2SPEED, false);
			ArmRenderer->FindAnimation("Up_Tool1")->Inters[4] = TOOL1LASTANI;
			ArmRenderer->FindAnimation("Up_Tool2")->Inters[2] = TOOL2LASTANI;
			ArmRenderer->CreateAnimation("Up_Harvest", "Up_Player_arm_Harvest", 0, 3, HARVESTSPEED, false);
			ArmRenderer->CreateAnimation("Up_Idle_Item", "Up_Player_arm_Item", 0, 0);
			ArmRenderer->CreateAnimation("Up_Run_Item", "Up_Player_arm_Item", 1, 8, RUNSPEED1);
			ArmRenderer->CreateAnimation("Up_Tool3", "Up_Player_arm_Tool3", 0, 5, TOOL3SPEED, false);
		}

		// Down
		{
			ArmRenderer->CreateAnimation("Down_Idle", "Down_Player_arm", 0, 0);
			ArmRenderer->CreateAnimation("Down_Run", "Down_Player_arm", 1, 8, RUNSPEED1);
			ArmRenderer->CreateAnimation("Down_Tool1", "Down_Player_arm_Tool1", 0, 4, TOOL1SPEED, false);
			ArmRenderer->CreateAnimation("Down_Tool2", "Down_Player_arm_Tool2", 0, 2, TOOL2SPEED, false);
			ArmRenderer->FindAnimation("Down_Tool1")->Inters[4] = TOOL1LASTANI;
			ArmRenderer->FindAnimation("Down_Tool2")->Inters[2] = TOOL2LASTANI;
			ArmRenderer->CreateAnimation("Down_Harvest", "Down_Player_arm_Harvest", 0, 3, HARVESTSPEED, false);
			ArmRenderer->CreateAnimation("Down_OpenBox", "Down_Player_arm_Harvest", 3, 3, 5.0f, false);
			ArmRenderer->CreateAnimation("Down_Idle_Item", "Down_Player_arm_Item", 0, 0);
			ArmRenderer->CreateAnimation("Down_Run_Item", "Down_Player_arm_Item", 1, 8, RUNSPEED1);
			ArmRenderer->CreateAnimation("Down_Tool3", "Down_Player_arm_Tool3", 0, 5, TOOL3SPEED, false);
		}

		// Right
		{
			ArmRenderer->CreateAnimation("Right_Idle", "Right_Player_arm", 0, 0);
			ArmRenderer->CreateAnimation("Right_Run", "Right_Player_arm", 1, 6, RUNSPEED2);
			ArmRenderer->CreateAnimation("Right_Tool1", "Right_Player_arm_Tool1", 0, 4, TOOL1SPEED, false);
			ArmRenderer->CreateAnimation("Right_Tool2", "Right_Player_arm_Tool2", 0, 2, TOOL2SPEED, false);
			ArmRenderer->FindAnimation("Right_Tool1")->Inters[4] = TOOL1LASTANI;
			ArmRenderer->FindAnimation("Right_Tool2")->Inters[2] = TOOL2LASTANI;
			ArmRenderer->CreateAnimation("Right_Harvest", "Right_Player_arm_Harvest", 0, 3, HARVESTSPEED, false);
			ArmRenderer->CreateAnimation("Right_Idle_Item", "Right_Player_arm_Item", 0, 0);
			ArmRenderer->CreateAnimation("Right_Run_Item", "Right_Player_arm_Item", 1, 6, RUNSPEED2);
			ArmRenderer->CreateAnimation("Right_Tool3", "Right_Player_arm_Tool3", 0, 5, TOOL3SPEED, false);
		}

		// Left
		{
			ArmRenderer->CreateAnimation("Left_Idle", "Left_Player_arm", 0, 0);
			ArmRenderer->CreateAnimation("Left_Run", "Left_Player_arm", 1, 6, RUNSPEED2);
			ArmRenderer->CreateAnimation("Left_Tool1", "Left_Player_arm_Tool1", 0, 4, TOOL1SPEED, false);
			ArmRenderer->CreateAnimation("Left_Tool2", "Left_Player_arm_Tool2", 0, 2, TOOL2SPEED, false);
			ArmRenderer->FindAnimation("Left_Tool1")->Inters[4] = TOOL1LASTANI;
			ArmRenderer->FindAnimation("Left_Tool2")->Inters[2] = TOOL2LASTANI;
			ArmRenderer->CreateAnimation("Left_Harvest", "Left_Player_arm_Harvest", 0, 3, HARVESTSPEED, false);
			ArmRenderer->CreateAnimation("Left_Idle_Item", "Left_Player_arm_Item", 0, 0);
			ArmRenderer->CreateAnimation("Left_Run_Item", "Left_Player_arm_Item", 1, 6, RUNSPEED2);
			ArmRenderer->CreateAnimation("Left_Tool3", "Left_Player_arm_Tool3", 0, 5, TOOL3SPEED, false);
		}
	}

	// Hair
	{
		//Up
		{
			HairRenderer->CreateAnimation("Up_Idle", "Up_Player_hair", 0, 0);
			HairRenderer->CreateAnimation("Up_Run", "Up_Player_hair", 1, 8, RUNSPEED1);
			HairRenderer->CreateAnimation("Up_Tool1", "Up_Player_hair_Tool1", 0, 4, TOOL1SPEED, false);
			HairRenderer->CreateAnimation("Up_Tool2", "Up_Player_hair_Tool2", 0, 2, TOOL2SPEED, false);
			HairRenderer->FindAnimation("Up_Tool1")->Inters[4] = TOOL1LASTANI;
			HairRenderer->FindAnimation("Up_Tool2")->Inters[2] = TOOL2LASTANI;
			HairRenderer->CreateAnimation("Up_Harvest", "Up_Player_hair_Harvest", 0, 3, HARVESTSPEED, false);
			HairRenderer->CreateAnimation("Up_Tool3", "Up_Player_hair_Tool3", 0, 5, TOOL3SPEED, false);
		}

		//Down
		{
			HairRenderer->CreateAnimation("Down_Idle", "Down_Player_hair", 0, 0);
			HairRenderer->CreateAnimation("Down_Run", "Down_Player_hair", 1, 8, RUNSPEED1);
			HairRenderer->CreateAnimation("Down_Tool1", "Down_Player_hair_Tool1", 0, 4, TOOL1SPEED, false);
			HairRenderer->CreateAnimation("Down_Tool2", "Down_Player_hair_Tool2", 0, 2, TOOL2SPEED, false);
			HairRenderer->FindAnimation("Down_Tool1")->Inters[4] = TOOL1LASTANI;
			HairRenderer->FindAnimation("Down_Tool2")->Inters[2] = TOOL2LASTANI;
			HairRenderer->CreateAnimation("Down_Harvest", "Down_Player_hair_Harvest", 0, 3, HARVESTSPEED, false);
			HairRenderer->CreateAnimation("Down_OpenBox", "Down_Player_hair_Harvest", 3, 3, 5.0f, false);
			HairRenderer->CreateAnimation("Down_Tool3", "Down_Player_hair_Tool3", 0, 5, TOOL3SPEED, false);
		}

		//Right
		{
			HairRenderer->CreateAnimation("Right_Idle", "Right_Player_hair", 0, 0);
			HairRenderer->CreateAnimation("Right_Run", "Right_Player_hair", 1, 6, RUNSPEED2);
			HairRenderer->CreateAnimation("Right_Tool1", "Right_Player_hair_Tool1", 0, 4, TOOL1SPEED, false);
			HairRenderer->CreateAnimation("Right_Tool2", "Right_Player_hair_Tool2", 0, 2, TOOL2SPEED, false);
			HairRenderer->FindAnimation("Right_Tool1")->Inters[4] = TOOL1LASTANI;
			HairRenderer->FindAnimation("Right_Tool2")->Inters[2] = TOOL2LASTANI;
			HairRenderer->CreateAnimation("Right_Harvest", "Right_Player_hair_Harvest", 0, 3, HARVESTSPEED, false);
			HairRenderer->CreateAnimation("Right_Tool3", "Right_Player_hair_Tool3", 0, 5, TOOL3SPEED, false);
		}

		//Left
		{
			HairRenderer->CreateAnimation("Left_Idle", "Left_Player_hair", 0, 0);
			HairRenderer->CreateAnimation("Left_Run", "Left_Player_hair", 1, 6, RUNSPEED2);
			HairRenderer->CreateAnimation("Left_Tool1", "Left_Player_hair_Tool1", 0, 4, TOOL1SPEED, false);
			HairRenderer->CreateAnimation("Left_Tool2", "Left_Player_hair_Tool2", 0, 2, TOOL2SPEED, false);
			HairRenderer->FindAnimation("Left_Tool1")->Inters[4] = TOOL1LASTANI;
			HairRenderer->FindAnimation("Left_Tool2")->Inters[2] = TOOL2LASTANI;
			HairRenderer->CreateAnimation("Left_Harvest", "Left_Player_hair_Harvest", 0, 3, HARVESTSPEED, false);
			HairRenderer->CreateAnimation("Left_Tool3", "Left_Player_hair_Tool3", 0, 5, TOOL3SPEED, false);
		}

		// Water
		WaterRenderer->CreateAnimation("Water", "WaterAnimation", 0, 9, WATERSPEED, false);
		WaterRenderer->ChangeAnimation("Water");
	}
	
	// Player Collision
	BodyCollision = CreateCollision(CollisionOrder::Player);
	BodyCollision->SetCollisionPos(float4{0, 9} * RENDERRATIO);
	BodyCollision->SetCollisionScale(TILESIZE * RENDERRATIO);

	// Debug Collision
	UpCollision = { 0, 8 * RENDERRATIO };
	LeftCollision = { -8 * RENDERRATIO, 12 * RENDERRATIO };
	RightCollision = { 8 * RENDERRATIO, 12 * RENDERRATIO };
	DownCollision = { 0 , 16 * RENDERRATIO };

	Dir = PlayerDir::Right;
	ChangeState(PlayerState::Idle);
}

void Player::Update(float _Delta)
{
	if (true == IsUpdate)
	{
		StateUpdate(_Delta);
		if (true == GameEngineInput::IsDown(VK_F2))
		{
			CollisionDebug = !CollisionDebug;
		}
	}

	if (true == WaterRenderer->IsAnimationEnd())
	{
		WaterRenderer->Off();
	}

	if (nullptr == CurItem)
	{
		if (PlayerState::Idle == State)
		{
			ChangeAnimationState("Idle");
		}
		CurItemRenderer->Off();
		return;
	}

	if (PlayerState::Idle == State || PlayerState::Run == State)
	{
		if (ItemType::Resources == CurItem->GetItemType() || ItemType::Crops == CurItem->GetItemType() || ItemType::Seed == CurItem->GetItemType())
		{
			CurItemRenderer->SetTexture("Inventory_" + CurItem->GetItemName());
			CurItemRenderer->On();
		}
		else
		{
			CurItemRenderer->Off();
		}
	}
	else
	{
		CurItemRenderer->Off();
	}

	if (PlayerState::Idle == State)
	{
		ChangeAnimationState("Idle");
	}
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Run:
		return RunUpdate(_Delta);
	case PlayerState::Tool:
		return ToolUpdate(_Delta);
	case PlayerState::Tool2:
		return Tool2Update(_Delta);
	case PlayerState::Tool3:
		return Tool3Update(_Delta);
	case PlayerState::Harvest:
		return HarvestUpdate(_Delta);
	case PlayerState::OpenBox:
		return OpenBoxUpdate(_Delta);
	default:
		break;
	}
}

void Player::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::Tool:
			ToolStart();
			break;
		case PlayerState::Tool2:
			Tool2Start();
			break;
		case PlayerState::Tool3:
			Tool3Start();
			break;
		case PlayerState::Harvest:
			HarvestStart();
			break;
		case PlayerState::OpenBox:
			OpenBoxStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Player::DirCheck()
{
	int CheckDir = PlayerDir::Null;
	bool ChangeDir = false;

	if (true == GameEngineInput::IsPress('A'))
	{
		CheckDir += PlayerDir::Left;
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		CheckDir += PlayerDir::Right;
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		CheckDir += PlayerDir::Up;
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		CheckDir += PlayerDir::Down;
	}

	if (PlayerDir::Null != CheckDir)
	{
		Dir = CheckDir;
		ChangeDir = true;
	}

	if (PlayerDir::Null != CheckDir && true == ChangeDir)
	{
		ChangeAnimationState(CurState);
	}
}

void Player::ToolDirCheck()
{
	float4 Index = TileLimit();
	float4 FarmerIndex = PlayLevel->GetUITileMap()->PosToIndex(GetPos() + DownCollision);

	if (Index.X < FarmerIndex.X)
	{
		Dir = PlayerDir::Left;
		ToolDir = "Left_";
	}
	else if (Index.X > FarmerIndex.X)
	{
		Dir = PlayerDir::Right;
		ToolDir = "Right_";
	}
	else if (Index.Y < FarmerIndex.Y)
	{
		Dir = PlayerDir::Up;
		ToolDir = "Up_";
	}
	else
	{
		Dir = PlayerDir::Down;
		ToolDir = "Down_";
	}
}

float4 Player::TileLimit()
{
	float4 Index = PlayLevel->GetUITileMap()->PosToIndex(ContentMouse::MainMouse->GetMousePos());
	float4 FarmerIndex = PlayLevel->GetUITileMap()->PosToIndex(GetPos() + DownCollision);

	if (Index.iX() <= FarmerIndex.iX() - 1)
	{
		Index.X = FarmerIndex.X - 1.0f;
		if (Index.iY() <= FarmerIndex.iY() - 1)
		{
			Index.Y = FarmerIndex.Y - 1.0f;
		}
		else if (Index.iY() >= FarmerIndex.iY() + 1)
		{
			Index.Y = FarmerIndex.Y + 1.0f;
		}
		else
		{
			Index.Y = FarmerIndex.Y;
		}
	}
	else if (Index.iX() >= FarmerIndex.iX() + 1)
	{
		Index.X = FarmerIndex.X + 1.0f;
		if (Index.iY() <= FarmerIndex.iY() - 1)
		{
			Index.Y = FarmerIndex.Y - 1.0f;
		}
		else if (Index.iY() >= FarmerIndex.iY() + 1)
		{
			Index.Y = FarmerIndex.Y + 1.0f;
		}
		else
		{
			Index.Y = FarmerIndex.Y;
		}
	}
	else
	{
		Index.X = FarmerIndex.X;
		if (Index.iY() <= FarmerIndex.iY() - 1)
		{
			Index.Y = FarmerIndex.Y - 1.0f;
		}
		else if (Index.iY() >= FarmerIndex.iY() + 1)
		{
			Index.Y = FarmerIndex.Y + 1.0f;
		}
		else
		{
			Index.Y = FarmerIndex.Y;
		}
	}
	return Index;
}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	if (PlayerDir::Right == (Dir & PlayerDir::Right))
	{
		AnimationName = "Right_";
	}
	else if (PlayerDir::Left == (Dir & PlayerDir::Left))
	{
		AnimationName = "Left_";
	}
	else if (PlayerDir::Up == (Dir & PlayerDir::Up))
	{
		AnimationName = "Up_";
	}
	else if (PlayerDir::Down == (Dir & PlayerDir::Down))
	{
		AnimationName = "Down_";
	}

	// ShirtPos Setting
	ShirtRenderer->SetRenderPos({ 0, 2 * RENDERRATIO });

	if (PlayerState::OpenBox == State)
	{
		AnimationName = "Down_";
	}

	// Animation Change
	AnimationName += _StateName;
	CurState = _StateName;
	BodyRenderer->ChangeAnimation(AnimationName);
	PantsRenderer->ChangeAnimation(AnimationName);
	ShirtRenderer->ChangeAnimation(AnimationName);
	HairRenderer->ChangeAnimation(AnimationName);

	if (nullptr != CurItem && ("Idle" == _StateName || "Run" == _StateName))
	{
		if (ItemType::Resources == CurItem->GetItemType() || ItemType::Crops == CurItem->GetItemType() || ItemType::Seed == CurItem->GetItemType())
		{
			ArmRenderer->ChangeAnimation(AnimationName + "_Item", static_cast<int>(BodyRenderer->GetCurFrame()), true);
			return;
		}
	}
	ArmRenderer->ChangeAnimation(AnimationName, static_cast<int>(BodyRenderer->GetCurFrame()), true);
}

void Player::SetCollisionTexture(const std::string& _CollisionTexture)
{
	CollisionTexture = ResourcesManager::GetInst().FindTexture(_CollisionTexture);
	if (nullptr == CollisionTexture)
	{
		MsgBoxAssert(_CollisionTexture + "는 존재하지 않는 CollisionTexture입니다.");
	}
}

int Player::GetTileColor(unsigned int _Color, float4 _Pos /*= float4::ZERO*/)
{
	if (nullptr == CollisionTexture)
	{
		MsgBoxAssert("CollisionTexture가 세팅되어 있지 않습니다.");
	}
	float4 Pos = GetPos();
	Pos += _Pos;
	Pos *= 1.0f / RENDERRATIO;
	return CollisionTexture->GetColor(_Color, Pos);
}

void Player::Render(float _Delta)
{
	// Debug Renderer

	if (true == CollisionDebug)
	{
		HDC handle = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

		CollisionData PlayerCollision;
		PlayerCollision.Pos = WindowActorPos();
		PlayerCollision.Scale = { 4,4 };
		PlayerCollision.Pos = WindowActorPos() + UpCollision;
		Rectangle(handle, PlayerCollision.iLeft(), PlayerCollision.iTop(), PlayerCollision.iRight(), PlayerCollision.iBot());

		PlayerCollision.Pos = WindowActorPos() + RightCollision;
		Rectangle(handle, PlayerCollision.iLeft(), PlayerCollision.iTop(), PlayerCollision.iRight(), PlayerCollision.iBot());

		PlayerCollision.Pos = WindowActorPos() + LeftCollision;
		Rectangle(handle, PlayerCollision.iLeft(), PlayerCollision.iTop(), PlayerCollision.iRight(), PlayerCollision.iBot());

		PlayerCollision.Pos = WindowActorPos() + DownCollision;
		Rectangle(handle, PlayerCollision.iLeft(), PlayerCollision.iTop(), PlayerCollision.iRight(), PlayerCollision.iBot());
	}
}

void Player::ToolCollisionCreate(CollisionOrder _CollisionType)
{
	float4 CollisionPos = PlayLevel->GetUITileMap()->IndexToPos(TileLimit().iX(), TileLimit().iY());
	ToolCollision = CreateCollision(_CollisionType);
	ToolCollision->SetCollisionScale(TILESIZE * RENDERRATIO * 0.8f);
	ToolCollision->SetCollisionPos(CollisionPos + TILESIZE.Half() * RENDERRATIO - GetPos());
}

void Player::StopPlayer()
{
	IsUpdate = false;
	Player::MainPlayer->ChangeState(PlayerState::Idle);
	EffectPlayer.Stop();
}

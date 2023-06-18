#pragma once

enum class UpdateOrder
{
	Map,
	Player,
	Inventory,
};

enum class RenderOrder
{
	BackGround,
	PlayBelow,
	Shadow,
	Play,
	Pants,
	Shirt,
	Hair,
	Hat,
	Arm,
	Creature,
	PlayOver_Building,
	PlayOver,
	UI,
	Inventory_Item,
	UIMouse,
};

enum class CollisionOrder
{
	Map,
	Player,
	Npc,
	Axe,
	PickAxe,
	Hoe,
	WateringCan,
	Resources,
	Item,
	Crops,
	Button,
	Shop,
	UI,
	Inventory_Item,
	UIMouse,
};
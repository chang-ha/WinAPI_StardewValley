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
	UI,
	Inventory_Item,
	UIMouse,
};
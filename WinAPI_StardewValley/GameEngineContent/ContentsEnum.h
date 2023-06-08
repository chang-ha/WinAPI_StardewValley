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
	Axe,
	PickAxe,
	Hoe,
	WateringCan,
	Resources,
	Item,
	Button,
	UI,
	Inventory_Item,
	UIMouse,
};
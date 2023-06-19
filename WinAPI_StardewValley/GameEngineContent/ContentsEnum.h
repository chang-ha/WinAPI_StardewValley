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
	PlayOver,
	UI,
	Inventory_Item,
	UIMouse,
};

enum class CollisionOrder
{
	Map,
	Button,
	Player,
	Npc,
	Axe,
	PickAxe,
	Hoe,
	WateringCan,
	Resources,
	Item,
	Crops,
	Shop,
	UI,
	Inventory_Item,
	UIMouse,
};
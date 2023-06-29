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
	Shadow,
	PlayBelow,
	Play,
	PlayOver,
	UI,
	UI_Money,
	Inventory_Item,
	UIMouse,
	FadeObject,
};

enum class CollisionOrder
{
	Map,
	Button,
	Player,
	PlayerAction,
	Npc,
	Axe,
	PickAxe,
	Hoe,
	Sickle,
	WateringCan,
	Resources,
	Item,
	Crops,
	Shop,
	UI,
	Inventory_Item,
	UIMouse,
};
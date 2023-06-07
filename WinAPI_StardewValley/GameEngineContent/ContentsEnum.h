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
	UIMouse,
};

enum class CollisionOrder
{
	Map,
	Player,
	Resources,
	Item,
	Button,
	UI,
	UIMouse,
};
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
	Actor,
	Player,
	Button,
	UI
};
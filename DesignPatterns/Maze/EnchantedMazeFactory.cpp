#include "EnchantedMazeFactory.h"
#include "EnchantedRoom.h"
#include "DoorNeedingSpell.h"
using namespace MazeApp;

EnchantedMazeFactory::EnchantedMazeFactory() {}

Room* EnchantedMazeFactory::MakeRoom(int no) const
{
	return new EnchantedRoom(no, CastSpell());
}

Door* EnchantedMazeFactory::MakeDoor(Room* room1, Room* room2) const
{
	return new DoorNeedingSpell(room1, room2);
}

Spell* EnchantedMazeFactory::CastSpell() const
{
	return new Spell;
}
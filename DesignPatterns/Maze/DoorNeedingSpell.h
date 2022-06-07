#pragma once
#include "Door.h"
namespace MazeApp
{
	class DoorNeedingSpell :
		public Door
	{
	public:
		DoorNeedingSpell(Room* room1, Room* room2);
	};
}


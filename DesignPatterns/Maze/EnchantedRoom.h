#pragma once
#include "Room.h"
#include "Spell.h"

namespace MazeApp
{
	class EnchantedRoom :
		public Room
	{
	public:
		EnchantedRoom(int no, Spell* spell);
	};
}



#pragma once
#include "MazeFactory.h"
#include "Spell.h"

namespace MazeApp
{
	class EnchantedMazeFactory :
		public MazeFactory
	{
	public:
		EnchantedMazeFactory();

		virtual Room* MakeRoom(int no) const;
		virtual Door* MakeDoor(Room* room1, Room* room2) const;

	protected:
		Spell* CastSpell() const;
	};
}



#pragma once
#include "MapSite.h"
#include "Room.h"

namespace MazeApp {
	class Door : public MapSite
	{
	public:
		Door(Room* = 0, Room* = 0);

		virtual void Enter();
		Room* OtherSideFrom(Room*);

	private:
		Room* mRoom1;
		Room* mRoom2;
		bool mIsOpen;
	};
}

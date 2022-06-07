#pragma once
#include <vector>
#include "Room.h"

namespace MazeApp
{
	class Maze 
	{
	public:
		Maze();

		void AddRoom(Room*);
		Room* RoomNo(int) const;
	private:
		std::vector<Room*> mRooms;
	};
}
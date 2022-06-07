#include "Maze.h"
using namespace MazeApp;

Maze::Maze() {}

void Maze::AddRoom(Room* room)
{
	mRooms.push_back(room);
}

Room* Maze::RoomNo(int no) const
{
	for (size_t i = 0; i < mRooms.size(); i++)
	{
		if (mRooms[i]->GetRoomNo() == no)
			return mRooms[i];
	}

	return 0;
}
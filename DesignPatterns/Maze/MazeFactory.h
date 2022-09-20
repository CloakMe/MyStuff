#pragma once
#include "Door.h"
#include "Maze.h"
#include "Wall.h"

namespace MazeApp
{
	class MazeFactory
	{
	public:
		MazeFactory();

		virtual Maze* MakeMaze() const;
		virtual Wall* MakeWall() const;
		virtual Room* MakeRoom(int no) const;
		virtual Door* MakeDoor(Room* room1, Room* room2) const;
	};
}

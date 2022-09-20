#include "MazeFactory.h"
using namespace MazeApp;

MazeFactory::MazeFactory() {}

Maze* MazeFactory::MakeMaze() const
{
	return new Maze;
}

Wall* MazeFactory::MakeWall() const
{
	return new Wall;
}

Room* MazeFactory::MakeRoom(int no) const
{
	return new Room(no);
}

Door* MazeFactory::MakeDoor(Room* room1, Room* room2) const
{
	return new Door(room1, room2);
}
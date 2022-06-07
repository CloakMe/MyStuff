#include "MazeGame.h"
#include "Maze.h"
using namespace MazeApp;

Maze* MazeGame::CreateMaze(MazeBuilder& mazeBuilder)
{
	mazeBuilder.BuildMaze();
	
	mazeBuilder.BuildRoom(1);
	mazeBuilder.BuildRoom(2);
	mazeBuilder.BuildDoor(1,2);
	mazeBuilder.BuildRoom(3);
	mazeBuilder.BuildDoor(1, 3);
	mazeBuilder.BuildRoom(4);
	mazeBuilder.BuildDoor(1, 4);
	mazeBuilder.BuildRoom(5);
	mazeBuilder.BuildDoor(1, 5);

	return mazeBuilder.GetMaze();
}

Maze* MazeGame::CreateMaze(MazeFactory& mazeFactory)
{
	Maze* aMaze = mazeFactory.MakeMaze();

	Room* room1 = mazeFactory.MakeRoom(1);
	Room* room2 = mazeFactory.MakeRoom(2);
	Door* aDoor = mazeFactory.MakeDoor(room1, room2);

	room1->SetSide(North, mazeFactory.MakeWall());
	room1->SetSide(East, aDoor);
	room1->SetSide(South, mazeFactory.MakeWall());
	room1->SetSide(West, mazeFactory.MakeWall());

	room2->SetSide(North, mazeFactory.MakeWall());
	room2->SetSide(East, mazeFactory.MakeWall());
	room2->SetSide(South, mazeFactory.MakeWall());
	room2->SetSide(West, aDoor);

	aMaze->AddRoom(room1);
	aMaze->AddRoom(room2);
	
	return aMaze;
}
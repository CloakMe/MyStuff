#include <typeinfo>
#include <exception>
#include "StandardMazeBuilder.h"
#include "Wall.h"
#include "Door.h"
using namespace MazeApp;

StandardMazeBuilder::StandardMazeBuilder() {
	mCurrentMaze = 0;
}

void StandardMazeBuilder::BuildMaze()
{
	mCurrentMaze = new Maze;
}

Maze* StandardMazeBuilder::GetMaze() {
	return mCurrentMaze;
}

void StandardMazeBuilder::BuildRoom(int no)
{
	if (!mCurrentMaze->RoomNo(no))
	{
		Room* room = new Room(no);
		mCurrentMaze->AddRoom(room);

		room->SetSide(North, new Wall);
		room->SetSide(South, new Wall);
		room->SetSide(East, new Wall);
		room->SetSide(West, new Wall);
	}
}

void StandardMazeBuilder::BuildDoor(int no1, int no2)
{
	Room* room1 = mCurrentMaze->RoomNo(no1);
	Room* room2 = mCurrentMaze->RoomNo(no2);
	Door* door = new Door(room1, room2);

	Direction d = CommonWall(room1, room2);
	int otherD = (d + 2) % 4;
	room1->SetSide(d, door);
	room2->SetSide((Direction)otherD, door);
}

Direction StandardMazeBuilder::CommonWall(Room* room1, Room* room2) 
{
	if (typeid( *(room1->GetSide(North) ) ) == typeid(Wall) && 
		( typeid( *(room2->GetSide(South) ) ) == typeid(Wall) ||
	      typeid( *(room2->GetSide(South) ) ) == typeid(Door) )
		)
		return North;

	if (typeid(*(room1->GetSide(South))) == typeid(Wall) &&
		(typeid(*(room2->GetSide(North))) == typeid(Wall) ||
			typeid(*(room2->GetSide(North))) == typeid(Door))
		)
		return South;

	if (typeid(*(room1->GetSide(East))) == typeid(Wall) &&
		(typeid(*(room2->GetSide(West))) == typeid(Wall) ||
			typeid(*(room2->GetSide(West))) == typeid(Door))
		)
		return East;

	if (typeid(*(room1->GetSide(West))) == typeid(Wall) &&
		(typeid(*(room2->GetSide(East))) == typeid(Wall) ||
			typeid(*(room2->GetSide(East))) == typeid(Door))
		)
		return West;
	
	throw std::exception("could not get direction!");
}
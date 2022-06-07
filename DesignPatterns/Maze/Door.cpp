#include "Door.h"
using namespace MazeApp;

Door::Door(Room* room1, Room* room2)
{
	mRoom1 = room1;
	mRoom2 = room2;
	mIsOpen = false;
}

Room* Door::OtherSideFrom(Room* room)
{
	if (room == mRoom1)
		return mRoom2;
	if (room == mRoom2)
		return mRoom1;

	return 0;
}

void Door::Enter()
{

}
#include "Room.h"
using namespace MazeApp;

Room::Room(int roomNo)
{
	mRoomNumber = roomNo;
	for (int i = North; i <= West; i++)
	{
		mSides[i] = 0;
	}
}

MapSite* Room::GetSide(Direction d) const
{
	return mSides[d];
}

void Room::SetSide(Direction d, MapSite* mapSite)
{
	if (mSides[d] == mapSite)
		return;

	if (mSides[d] > 0)
		delete mSides[d];

	mSides[d] = mapSite;
}

int Room::GetRoomNo() const
{
	return mRoomNumber;
}

void Room::Enter()
{

}
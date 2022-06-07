#pragma once
#include "MapSite.h"
#include "Direction.h"
namespace MazeApp 
{
	class Room : public MapSite {
	public:
		Room(int roomNo);
	
		MapSite* GetSide(Direction) const;
		void SetSide(Direction, MapSite*);
		int GetRoomNo() const;

		virtual void Enter();

	private:
		MapSite* mSides[4];
		int mRoomNumber;
	};
}

#pragma once
#include "MazeBuilder.h"
namespace MazeApp
{
	class StandardMazeBuilder : public MazeBuilder
	{
	public:
		StandardMazeBuilder();

		virtual void BuildMaze();
		virtual void BuildRoom(int);
		virtual void BuildDoor(int, int);

		virtual Maze* GetMaze();
	private:
		Direction CommonWall(Room*, Room*);
		Maze* mCurrentMaze;
	};
}

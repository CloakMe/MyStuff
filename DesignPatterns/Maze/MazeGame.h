#pragma once
#include "Maze.h"
#include "MazeBuilder.h"
#include "MazeFactory.h"

namespace MazeApp
{
	class MazeGame
	{
	public:
		Maze* CreateMaze(MazeBuilder& mazeBuilder);
		Maze* CreateMaze(MazeFactory& mazeBuilder);
	};
}
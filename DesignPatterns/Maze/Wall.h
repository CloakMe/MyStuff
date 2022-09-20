#pragma once
#include "MapSite.h"

namespace MazeApp {
	class Wall : public MapSite
	{
	public:
		Wall();

		virtual void Enter();
	};
}

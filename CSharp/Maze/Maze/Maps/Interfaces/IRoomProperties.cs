using System;
using System.Collections.Generic;
using System.Drawing;

namespace MazeGame.Maps.Interfaces
{
    public interface IRoomProperties
    {
        ICollection<ExitPosition> ExitPositions { get; }

        Point MapCoordinates { get; }

        bool Revealed { get; }

        char RoomName { get; }
    }
}

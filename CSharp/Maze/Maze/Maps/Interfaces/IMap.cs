using System;
using System.Collections.Generic;
using System.Drawing;
using MazeGame.Rooms.Interfaces;

namespace MazeGame.Maps.Interfaces
{
    public interface IMap
    {
        IRoomProperties[,] DeliverMap();

        void AddRoom(IRoom iRoom, Point position, ICollection<ExitPosition> exitPositions);
    }
}

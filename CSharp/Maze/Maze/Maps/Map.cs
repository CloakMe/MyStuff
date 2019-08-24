using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MazeGame.Maps.Interfaces;
using MazeGame.Rooms.Interfaces;
using MazeGame.Common;
using System.Drawing;
using MazeGame.Exits.Interfaces;
using MazeGame.Rooms;
namespace MazeGame.Maps
{
    public class Map : IMap
    {
        public Map()
        {
            for (int i = 0; i < GlobalConstants.MapSize; i++)
                for (int j = 0; j < GlobalConstants.MapSize; j++)
                    roomProperties[i, j] = new RoomProperties(new Point(0,0), new List<ExitPosition>(), new Room("dummy", false));
        }

        //private Dictionary<IRoom, IRoomProperties> roomDistribution = new Dictionary<IRoom, IRoomProperties>();
        private IRoomProperties[,] roomProperties = new RoomProperties[GlobalConstants.MapSize, GlobalConstants.MapSize];

        public void AddRoom(IRoom iRoom, Point position, ICollection<ExitPosition> exitPositions)
        {
            roomProperties[position.X, position.Y] = new RoomProperties(position, exitPositions, iRoom);
            //roomDistribution.Add(iRoom, roomProperties[position.X, position.Y]);
        }

        public IRoomProperties[,] DeliverMap()
        {
            return roomProperties;
        }
    }
}

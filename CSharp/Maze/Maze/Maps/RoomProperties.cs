using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MazeGame.Maps.Interfaces;
using MazeGame.Rooms.Interfaces;
using System.Drawing;

namespace MazeGame.Maps
{
    public class RoomProperties : IRoomProperties
    {
        public RoomProperties(Point position, ICollection<ExitPosition> exitPositions, IRoom iRoom)
        {
            mapCoordinates = position;
            this.exitPositions = exitPositions;
            this.iRoom = iRoom;
        }
        private IRoom iRoom;
        private ICollection<ExitPosition> exitPositions = new List<ExitPosition>();
        public ICollection<ExitPosition> ExitPositions
        {
            get
            {
                List<ExitPosition> exitPositionsCopy = new List<ExitPosition>();
                foreach (ExitPosition ep in exitPositions)
                    exitPositionsCopy.Add(ep);

                return exitPositionsCopy;
            }
            private set
            {
                exitPositions = value;
            }
        }

        private Point mapCoordinates = new Point();
        public Point MapCoordinates 
        { 
            get
            {
                return new Point(mapCoordinates.X, mapCoordinates.Y);
            }
            private set
            {
                mapCoordinates = value;
            }
        }

        public bool Revealed
        {
            get
            {
                return this.iRoom.Revealed;
            }
        }

        public char RoomName
        {
            get
            {
                return this.iRoom.Name.FirstOrDefault();
            }
        }
    }
}

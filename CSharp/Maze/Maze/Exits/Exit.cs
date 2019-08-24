using MazeGame.Rooms.Interfaces;
using MazeGame.Exits.Interfaces;

namespace MazeGame.Exits
{
    public class Exit : IExit
    {
        public Exit(IRoom firstRoom, IRoom secondRoom, bool isLocked)
        {
            this.FirstRoom = firstRoom;
            this.SecondRoom = secondRoom;
            this.IsLocked = isLocked;
        }

        public IRoom FirstRoom { get; private set; }

        public IRoom SecondRoom { get; private set; }

        public bool IsLocked { get; private set; }
    }
}

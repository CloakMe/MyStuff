using MazeGame.Rooms.Interfaces;

namespace MazeGame.Exits.Interfaces
{
    public interface IExit
    {
        bool IsLocked { get; }

        IRoom FirstRoom { get; }

        IRoom SecondRoom { get; }
    }
}

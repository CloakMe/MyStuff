using MazeGame.Backpacks.Interfaces;
using MazeGame.Rooms.Interfaces;

namespace MazeGame.Players.Interfaces
{
    public interface IPlayer
    {
        string Name { get; }

        IRoom CurrentRoom { get; set; }

        IBackpack Backpack { get; }

        int Health { get; set; }
    }
}

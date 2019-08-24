using System.Collections.Generic;
using MazeGame.Rooms.Interfaces;
using MazeGame.Players.Interfaces;

namespace MazeGame.Engine.Interfaces
{
    public interface IInputProviderService
    {
        string ReadCommand(string playerName);

        IEnumerable<IPlayer> InitializePlayers(IRoom startRoom);
    }
}

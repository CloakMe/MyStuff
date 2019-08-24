using MazeGame.Players.Interfaces;

namespace MazeGame.Engine.Interfaces
{
    public interface  IGameEndService
    {
        void PrintDeathPlayerMessage();

        void PrintPlayerWinMessage();

        bool CheckIsPlayerAlive(IPlayer player);

        bool CheckIsPlayerWin(IPlayer player);
    }
}

using MazeGame.Players.Interfaces;

namespace MazeGame.Engine.Interfaces
{
    public interface IHealthService
    {
        void DecreasePlayersHealth(IPlayer player, bool isThereMonster);

        void IncreasePlayersHealthIfHealthpack(IPlayer player);

        void PrintHealthStatus(int healthPoints);
    }
}

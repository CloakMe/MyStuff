using System.Linq;
using MazeGame.Engine.Interfaces;
using MazeGame.Common;
using MazeGame.Renderer.Interfaces;
using MazeGame.Players.Interfaces;

namespace MazeGame.Engine
{
    public class GameEndService : IGameEndService
    {
        private readonly IRenderer renderer;

        public GameEndService(IRenderer renderer)
        {
            this.renderer = renderer;
        }

        public bool CheckIsPlayerAlive(IPlayer player)
        {
            if (player.Health < 1)
            {
                return false;
            }

            return true;
        }

        public bool CheckIsPlayerWin(IPlayer player)
        {
            if (player.Backpack.Items.Select(i => i.Name).Contains(RoomItems.AutoWinItem.ToString()))
            {
                return true;
            }

            return false;
        }

        public void PrintDeathPlayerMessage()
        {
            this.renderer.RenderMessageOnNewLine("Game over!");
        }

        public void PrintPlayerWinMessage()
        {
            this.renderer.RenderMessageOnNewLine("You win!");
        }
    }
}

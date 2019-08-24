using System.Linq;
using MazeGame.Common;
using MazeGame.Players.Interfaces;
using MazeGame.Renderer.Interfaces;
using MazeGame.Engine.Interfaces;

namespace MazeGame.Engine
{
    public class HealthService : IHealthService
    {
        private readonly IRenderer renderer;

        public HealthService(IRenderer renderer)
        {
            this.renderer = renderer;
        }

        public void DecreasePlayersHealth(IPlayer player, bool isThereMonster)
        {
            var items = player.Backpack.Items;
            var weapon = items.Where(i => i.Name == RoomItems.Sword.ToString() || i.Name == RoomItems.Bomb.ToString()).FirstOrDefault();

            if ((isThereMonster && weapon == null) || (weapon != null && weapon.IsUsed))
            {
                player.Health -= GlobalConstants.HealthPointsAddAndRemoveValue * 2;
            }
            else 
            {
                player.Health -= GlobalConstants.HealthPointsAddAndRemoveValue;
                if (weapon != null)
                {
                    weapon.IsUsed = true;
                }
            }
        }

        public void IncreasePlayersHealthIfHealthpack(IPlayer player)
        {
            var items = player.Backpack.Items;
            var helthpack = items.Where(i => i.Name == RoomItems.HealthPack.ToString()).FirstOrDefault();

            if (helthpack != null && !helthpack.IsUsed && player.Health < GlobalConstants.PlayerMaxHealthPoints)
            {
                player.Health += GlobalConstants.HealthPointsAddAndRemoveValue;
                helthpack.IsUsed = true;
            }
        }

        public void PrintHealthStatus(int healthPoints)
        {
            this.renderer.RenderMessageOnNewLine(healthPoints + " %");
        }
    }
}

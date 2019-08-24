using MazeGame.Players.Interfaces;
using MazeGame.Backpacks.Interfaces;
using MazeGame.Rooms.Interfaces;

namespace MazeGame.Players
{
    public class Player: IPlayer
    {
        public Player(string name, IBackpack backpack, int health, IRoom currentRoom)
        {
            this.Name = name;
            this.Backpack = backpack;
            this.Health = health;
            this.CurrentRoom = currentRoom;
        }

        public string Name { get; private set; }

        public IRoom CurrentRoom { get; set; }

        public IBackpack Backpack { get; private set; }

        public int Health { get; set; }
    }
}

using System.Collections.Generic;
using MazeGame.Common;
using MazeGame.Rooms.Interfaces;
using MazeGame.Renderer.Interfaces;
using MazeGame.Players.Interfaces;
using MazeGame.Players;
using MazeGame.Backpacks.Interfaces;
using MazeGame.Backpacks;
using MazeGame.Engine.Interfaces;

namespace MazeGame.Engine
{
    public class InputProviderService : IInputProviderService
    {
        private readonly IRenderer renderer;
        private readonly Reader reader;

        public InputProviderService(IRenderer renderer, Reader reader)
        {
            this.renderer= renderer;
            this.reader = reader;
        }

        public IEnumerable<IPlayer> InitializePlayers(IRoom startRoom)
        {
            this.renderer.RenderWithoutNewLine("Type the number of players: ");
            int numOfPlayers = this.reader.ReadInt();
            var listOfPlayers = new List<IPlayer>();

            for (int i = 0; i < numOfPlayers; i++)
            {
                this.renderer.RenderMessageOnNewLine("Type the name of your hero: ");
                string name = this.reader.Read();
                this.renderer.RenderMessageOnNewLine("Welcome, " + name + " !");
                IBackpack ibackpack = new Backpack(GlobalConstants.BackpackMaxWeight);
                IPlayer iplayer = new Player(name, ibackpack, GlobalConstants.PlayerMaxHealthPoints, startRoom);
                listOfPlayers.Add(iplayer);
            }

            return listOfPlayers;
        }

        public string ReadCommand(string playerName)
        {
            this.renderer.RenderWithoutNewLine(playerName + " :");

            return this.reader.Read();
        }
    }
}

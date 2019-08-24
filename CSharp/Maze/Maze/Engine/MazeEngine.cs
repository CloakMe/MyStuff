using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MazeGame.Players.Interfaces;
using MazeGame.Engine.Interfaces;
using MazeGame.Common;
using MazeGame.Rooms.Interfaces;
using MazeGame.Maps.Interfaces;

namespace MazeGame.Engine
{
    class MazeEngine
    {
        private readonly IInitializationService initializationService;
        private readonly IItemService itemService;
        private readonly IHealthService healthService;
        private readonly IGameEndService gameEndService;
        private readonly IHelperService helperService;
        private readonly IInputProviderService inputProviderService;
        private readonly ILocationService locationService;
        
        private ICollection<IPlayer> players;
        private IMap map;

        public MazeEngine(IItemService itemService, IHelperService helperService,
                ILocationService locationService, IInputProviderService inputProviderService,
                IGameEndService gameEndService, IHealthService healthService, IInitializationService initializationService)
        {
            this.initializationService = initializationService;
            this.itemService = itemService;
            this.locationService = locationService;
            this.inputProviderService = inputProviderService;
            this.helperService = helperService;
            this.gameEndService = gameEndService;
            this.healthService = healthService;
            this.players = new List<IPlayer>();
        }
        
        public void Initialize()
        {
            ICollection<IRoom> availableRooms = this.initializationService.InitializeRooms();
            map = this.initializationService.InitializeMap(availableRooms);
            var currentRoom = availableRooms.FirstOrDefault();
            
            var initializedItems = this.itemService.InitializeRoomItems();
            currentRoom.AddItemsCollection(initializedItems);

            IEnumerable<IPlayer> currentPlayers = this.inputProviderService.InitializePlayers(currentRoom);
            foreach (IPlayer iplayer in currentPlayers)
                players.Add(iplayer);
            this.helperService.PrintMainMenu();
        }

        public bool ProcessCommand()
        {
            for (int j = 0; j < this.players.Count; j++)
            {
                var player = this.players.ElementAt(j);

                try
                {
                    string command = this.inputProviderService.ReadCommand(player.Name);

                    if (command == MenuOptions.help.ToString())
                    {
                        this.helperService.PrintMainMenu();
                        j--;
                    }
                    else if (command == MenuOptions.items.ToString())
                    {
                        this.itemService.PrintItems(player.Backpack.Items.Select(i => i.Name),
                                                    player.CurrentRoom.Items.Select(i => i.Name),
                                                    player.Backpack.AvailableWeight);
                        j--;
                    }
                    else if (command == MenuOptions.location.ToString())
                    {
                        this.locationService.PrintCurrentLocation(player.CurrentRoom);
                        j--;
                    }
                    else if (command == MenuOptions.map.ToString())
                    {
                        IRoomProperties[,] iMapMatrix = map.DeliverMap();
                        this.locationService.PrintMap(iMapMatrix);
                        j--;
                    }
                    else if (command == MenuOptions.health.ToString())
                    {
                        this.healthService.PrintHealthStatus(player.Health);
                        j--;
                    }
                    else if (command == MenuOptions.clearScreen.ToString())
                    {
                        this.helperService.ClearScreen();
                        j--;
                    }
                    else if (command.Contains(MenuOptions.pickup.ToString()))
                    {
                        string itemName = command.Split(' ').Last();

                        if (this.itemService.PickItem(itemName, player))
                        {
                            this.helperService.PrintMessage("You successfuly added new item in your backpack!");
                        }
                    }
                    else if (command.Contains(MenuOptions.drop.ToString()))
                    {
                        string itemName = command.Split(' ').Last();

                        if (this.itemService.DropItem(itemName, player))
                        {
                            this.helperService.PrintMessage("You successfuly added new item in your backpack!");
                        }
                    }
                    else if (command.Contains(MenuOptions.go.ToString()))
                    {
                        string roomName = command.Split(' ').Last();

                        var key = this.itemService.GetKey(player.Backpack.Items);
                        var newRoom = this.locationService.ChangeLocation(roomName, player.CurrentRoom, key);
                        if (newRoom != null)
                        {
                            newRoom.AddItemsCollection(this.itemService.InitializeRoomItems());
                            this.healthService.DecreasePlayersHealth(player, newRoom.IsThereMonster);
                            player.CurrentRoom = newRoom;
                            this.helperService.PrintMessage("You successfuly entered ");
                            newRoom.Revealed = true;
                        }
                    }
                    else if (command == MenuOptions.quit.ToString())
                    {
                        return false;
                    }
                    else
                    {
                        throw new InvalidOperationException("Wrong command name !");
                    }

                    if (this.gameEndService.CheckIsPlayerWin(player))
                    {
                        this.gameEndService.PrintPlayerWinMessage();
                        return false;
                    }
                    else if (!this.gameEndService.CheckIsPlayerAlive(player))
                    {
                        this.gameEndService.PrintDeathPlayerMessage();
                        return false;
                    }

                    this.healthService.IncreasePlayersHealthIfHealthpack(player);
                    player.Backpack.RemoveUsedItems();
                }
                catch (InvalidOperationException ex)
                {
                    j--;
                    this.helperService.PrintMessage(ex.Message);
                }
            }

            return true;
        }
    }
}

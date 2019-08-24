using System;
using System.Collections.Generic;
using System.Linq;
using MazeGame.Common;
using MazeGame.Engine.Interfaces;
using MazeGame.Items.Interfaces;
using MazeGame.Items;
using MazeGame.Players.Interfaces;
using MazeGame.Renderer.Interfaces;

namespace MazeGame.Engine
{

    public class ItemService : IItemService
    {
        private readonly RandomGenerator random;
        private readonly IRenderer renderer;
        
        public ItemService(RandomGenerator random, IRenderer renderer)
        {
            this.random = random;
            this.renderer = renderer;
        }

        public ICollection<IItem> InitializeRoomItems()
        {
            var numbersOfItems = random.GetNumber(GlobalConstants.MinNumberOfItemsInRoom, GlobalConstants.MaxNumberOfItemsInRoom);
            var listOfItems = new List<IItem>();

            for (int i = 0; i < numbersOfItems; i++)
            {
                var item = this.random.GetNumber(0, Enum.GetNames(typeof(RoomItems)).Length);

                if (item == (int)RoomItems.Key)
                {
                    IItem iItem = new Item(RoomItems.Key.ToString(), GlobalConstants.KeyWeight);
                    listOfItems.Add(iItem);
                }
                else if (item == (int)RoomItems.Bomb)
                {
                    IItem iItem = new Item(RoomItems.Bomb.ToString(), GlobalConstants.BombWeight);
                    listOfItems.Add(iItem);
                }
                else if (item == (int)RoomItems.HealthPack)
                {
                    IItem iItem = new Item(RoomItems.HealthPack.ToString(), GlobalConstants.HealthPackWeight);
                    listOfItems.Add(iItem);
                }
                else if (item == (int)RoomItems.Sword)
                {
                    IItem iItem = new Item(RoomItems.Sword.ToString(), GlobalConstants.SwordWeight);
                    listOfItems.Add(iItem);
                }
                else if (item == (int)RoomItems.AutoWinItem)
                {
                    IItem iItem = new Item(RoomItems.AutoWinItem.ToString(), GlobalConstants.AutoWinItemWeigth);
                    listOfItems.Add(iItem);
                }
            }

            return listOfItems;
        }

        public bool CheckIsItemAvailable(string itemName, IEnumerable<IItem> items)
        {
            return items.Where(i => i.IsUsed == false).Select(i => i.Name.ToLower()).Contains(itemName.ToLower());
        }

        public bool PickItem(string name, IPlayer player)
        {
            Validator.CheckStringIfNullOrEmpty(name);

            var roomItems = player.CurrentRoom.Items;

            if (this.CheckIsItemAvailable(name, roomItems))
            {
                var itemFromRoom = roomItems.Where(i => i.Name.ToLower() == name.ToLower()).First();

                if (itemFromRoom.Weight <= player.Backpack.AvailableWeight)
                {
                    player.CurrentRoom.RemoveItem(itemFromRoom);
                    player.Backpack.AddItem(itemFromRoom);
                    
                    return true;
                }
                else
                {
                    throw new InvalidOperationException("You have too many items in your bag!");
                }
            }
            else
            {
                throw new InvalidOperationException("There is no item with this name !");
            }
        }

        public bool DropItem(string name, IPlayer player)
        {
            Validator.CheckStringIfNullOrEmpty(name);

            if (this.CheckIsItemAvailable(name, player.Backpack.Items))
            {
                var itemFromBag = player.Backpack.Items.Where(i => i.Name.ToLower() == name.ToLower()).First();
                player.Backpack.RemoveItem(itemFromBag);
                player.CurrentRoom.AddItem(itemFromBag);
                
                return true;
            }
            else
            {
                throw new InvalidOperationException("There is no item with this name !");
            }
        }

        public void PrintItems(IEnumerable<string> backPackItems, IEnumerable<string> roomItems, int availableWeight)
        {
            this.RenderItems(backPackItems, false);
            this.renderer.RenderMessageOnNewLine("Available weight: " + availableWeight);
            this.RenderItems(roomItems, true);
        }

        public IItem GetKey(ICollection<IItem> items)
        {
            return items.Where(i => i.Name == RoomItems.Key.ToString()).FirstOrDefault();
        }

        
        private void RenderItems(IEnumerable<string> items, bool isRoom)
        {
            if (isRoom)
            {
                if (items.Count() < 1)
                {
                    this.renderer.RenderMessageOnNewLine("There is no items in the room!");
                }
                else
                {
                    this.renderer.RenderMessageOnNewLine("Items available in the room: " + String.Join(", ", items));
                }
            }
            else
            {
                if (items.Count() < 1)
                {
                    this.renderer.RenderMessageOnNewLine("Your backpack is empty!");
                }
                else
                {
                    this.renderer.RenderMessageOnNewLine("Items available in your bag: " + String.Join(", ", items));
                }
            }
        }
    }
}

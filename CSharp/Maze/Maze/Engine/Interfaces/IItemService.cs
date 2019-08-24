using System.Collections.Generic;
using MazeGame.Items.Interfaces;
using MazeGame.Players.Interfaces;

namespace MazeGame.Engine.Interfaces
{
    public interface IItemService
    {
        ICollection<IItem> InitializeRoomItems();

        bool CheckIsItemAvailable(string itemName, IEnumerable<IItem> items);

        bool PickItem(string name, IPlayer player);
        
        bool DropItem(string name, IPlayer player);

        void PrintItems(IEnumerable<string> backPackItems, IEnumerable<string> roomItems, int availableWeight);

        IItem GetKey(ICollection<IItem> items);
    }
}

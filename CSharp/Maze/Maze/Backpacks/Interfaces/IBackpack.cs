using MazeGame.Items.Interfaces;
using System.Collections.Generic;

namespace MazeGame.Backpacks.Interfaces
{
    public interface IBackpack
    {
        int AvailableWeight { get; }

        ICollection<IItem> Items { get; }

        void AddItem(IItem item);

        void RemoveItem(IItem item);

        void RemoveUsedItems();
    }
}

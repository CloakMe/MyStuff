using System.Collections.Generic;
using MazeGame.Exits.Interfaces;
using MazeGame.Items.Interfaces;

namespace MazeGame.Rooms.Interfaces
{
    public interface IRoom
    {
        string Name { get; }

        bool Revealed { get; set; }

        bool IsThereMonster { get; }

        ICollection<IItem> Items { get; } 

        ICollection<IExit> Exits { get; }

        void AddExit(IExit exit);

        void RemoveExit(IExit exit);

        void AddItem(IItem item);

        void RemoveItem(IItem item);

        void AddItemsCollection(ICollection<IItem> items);
    }
}

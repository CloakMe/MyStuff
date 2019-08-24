using System.Collections.Generic;
using MazeGame.Exits.Interfaces;
using MazeGame.Items.Interfaces;
using MazeGame.Rooms.Interfaces;

namespace MazeGame.Rooms
{
    public class Room : IRoom
    {
        public Room(string name, bool isThereMonster)
        {
            this.items = new List<IItem>();
            this.exits = new List<IExit>();
            this.Name = name;
            this.IsThereMonster = isThereMonster;
            Revealed = false;
        }

        private readonly ICollection<IItem> items;
        private readonly ICollection<IExit> exits;

        public string Name { get; private set; }

        public bool Revealed{ get; set; }

        public bool IsThereMonster { get; private set; }

        public ICollection<IExit> Exits
        {
            get
            {
                return new List<IExit>(this.exits);
            }
        }

        public ICollection<IItem> Items {
            get
            {
                return new List<IItem>(this.items);
            }
        }

        public void AddExit(IExit exit)
        {
            this.exits.Add(exit);
        }

        public void RemoveExit(IExit exit)
        {
            this.exits.Remove(exit);
        }

        public void AddItem(IItem item)
        {
            this.items.Add(item);
        }
        
        public void RemoveItem(IItem item)
        {
            this.items.Remove(item);
        }

        public void AddItemsCollection(ICollection<IItem> items)
        {
            foreach (IItem item in items)
            {
                this.items.Add(item);
            }
        }
    }
}

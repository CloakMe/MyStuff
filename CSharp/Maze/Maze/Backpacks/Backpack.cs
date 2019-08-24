using System.Linq;
using System.Collections.Generic;
//using Common;
using MazeGame.Backpacks.Interfaces;
using MazeGame.Items.Interfaces;
//using Extentions;
namespace MazeGame.Backpacks
{
    public class Backpack : IBackpack
    {
        public Backpack(int backpackMaxWeight)
        {
            this.items = new List<IItem>();
            this.backpackMaxWeight = backpackMaxWeight;
        }

        private readonly ICollection<IItem> items;
        private int backpackMaxWeight;
        public int AvailableWeight
        {
            get
            {
                return this.backpackMaxWeight - this.Items.Sum(i => i.Weight);
            }
        }

        public ICollection<IItem> Items
        {
            get
            {
                return new List<IItem>(this.items);
            }
        }

        public void AddItem(IItem item)
        {
            this.items.Add(item);
        }

        public void RemoveItem(IItem item)
        {
            this.items.Remove(item);
        }

        public void RemoveUsedItems()
        {
            var usedItems = this.items.Where(i => i.IsUsed).ToList();

            for (int i = 0; i < usedItems.Count; i++)
            {
                this.RemoveItem(usedItems[i]);
            }
        }
    }
}

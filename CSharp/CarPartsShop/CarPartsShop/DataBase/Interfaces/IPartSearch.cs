using System.Collections.Generic;
using CarPartsShop.CarParts.Interfaces;
using CarPartsShop.Common;

namespace CarPartsShop.DataBase.Interfaces
{
    public interface IPartSearch
    {
        ICollection<ShopItem> SelectCarPartInShops(string partName);
    }
}

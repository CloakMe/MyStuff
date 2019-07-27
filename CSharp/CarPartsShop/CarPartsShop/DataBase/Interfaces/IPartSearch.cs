using System.Collections.Generic;
using CarPartsShop.CarParts.Interfaces;

namespace CarPartsShop.DataBase.Interfaces
{
    public interface IPartSearch
    {
        ICollection<ICarPart> SelectCarPartsByName(string partName);
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CarPartsShop.Cars.Interfaces;
using CarPartsShop.CarParts.Interfaces;
using CarPartsShop.Shops.Interfaces;

namespace CarPartsShop.DataBase.Interfaces
{
    public interface IDataBaseService
    {
        ICollection<ICar> GetCars { get;}
        ICollection<IShop> SelectShops();        
    }
}

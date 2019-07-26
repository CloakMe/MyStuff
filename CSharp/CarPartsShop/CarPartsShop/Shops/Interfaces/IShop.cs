using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CarPartsShop.CarParts.Interfaces;

namespace CarPartsShop.Shops.Interfaces
{
    public interface IShop
    {
        string Name { get; }
        Dictionary<ICarPart, double> CarPartsWithPrise { get; }
        void AddCarPartWithPrise(ICarPart iCarPart, double prise);
    }
}

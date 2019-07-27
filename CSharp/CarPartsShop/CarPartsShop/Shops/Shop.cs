using CarPartsShop.CarParts.Interfaces;
using CarPartsShop.Shops.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CarPartsShop.Shops
{
    public class Shop : IShop
    {
        public Shop(string name)
        {
            Name = name;
        }

        public string Name { get; private set; }

        Dictionary<ICarPart, double> carPartsWithPrise = new Dictionary<ICarPart, double>();
        public Dictionary<ICarPart, double> CarPartsWithPrise
        {
            get
            {
                Dictionary<ICarPart, double> carPartsWithPriseCopy =
                    new Dictionary<ICarPart, double>();
                foreach(KeyValuePair<ICarPart, double> kvp in carPartsWithPrise)
                {
                    carPartsWithPriseCopy.Add(kvp.Key, kvp.Value);
                }
                return carPartsWithPriseCopy;
            }
        }

        public void AddCarPartWithPrise(ICarPart iCarPart, double prise)
        {
            if(!carPartsWithPrise.ContainsKey(iCarPart))
                carPartsWithPrise.Add(iCarPart, prise);
        }
    }
}

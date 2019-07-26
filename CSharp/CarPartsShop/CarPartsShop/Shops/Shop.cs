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

        Dictionary<ICarPart, float> carPartsWithPrise = new Dictionary<ICarPart, float>();
        public Dictionary<ICarPart, float> CarPartsWithPrise
        {
            get
            {
                Dictionary<ICarPart, float> carPartsWithPriseCopy =
                    new Dictionary<ICarPart, float>();
                foreach(KeyValuePair<ICarPart, float> kvp in carPartsWithPrise)
                {
                    carPartsWithPriseCopy.Add(kvp.Key, kvp.Value);
                }
                return carPartsWithPriseCopy;
            }
        }

        public void AddCarPartWithPrise(ICarPart iCarPart, float prise)
        {
            carPartsWithPrise.Add(iCarPart, prise);
        }
    }
}

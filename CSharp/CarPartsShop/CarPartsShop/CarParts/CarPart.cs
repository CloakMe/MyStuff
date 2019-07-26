using CarPartsShop.CarParts.Interfaces;
using CarPartsShop.Cars.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CarPartsShop.CarParts
{
    public class CarPart : ICarPart
    {
        public CarPart(string name, int id = 0)
        {
            Name = name;
            Id = id;
        }

        public string Name { get; private set; }

        ICollection<ICar> cars = new List<ICar>();
        public ICollection<ICar> Cars
        {
            get
            {
                ICollection<ICar> carPartsCopy = new List<ICar>();
                foreach (ICar iCar in cars)
                {
                    carPartsCopy.Add(iCar);
                }
                return carPartsCopy;
            }
        }

        public void SetPartForCar(ICar iCar)
        {
            cars.Add(iCar);
        }

        public int Id { get; private set; }

    }
}

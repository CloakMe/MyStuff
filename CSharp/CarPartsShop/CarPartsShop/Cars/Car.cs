using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CarPartsShop.Cars.Interfaces;
using CarPartsShop.Common.Interfaces;

namespace CarPartsShop.Cars
{
    public class Car : ICar, IName
    {
        public Car(string brand, string model, int year, int id = 0)
        {
            Brand = brand;
            Model = model;
            Year = year;
            Id = id;
            Name = brand + ", " + model + ", " + year.ToString();
        }

        public string Brand { get; private set; }
        public string Model { get; private set; }
        public int Year { get; private set; }
        public int Id { get; private set; }
        public string Name { get; private set; }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CarPartsShop.Cars.Interfaces;

namespace CarPartsShop.CarParts.Interfaces
{
    public interface ICarPart
    {
        string Name { get; }
        ICollection<ICar> Cars { get;  }
        void SetPartForCar(ICar iCar);
        int Id { get; }
        ICollection<int> Ids { get; }
    }
}

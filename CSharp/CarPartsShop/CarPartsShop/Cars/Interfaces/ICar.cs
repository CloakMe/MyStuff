using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CarPartsShop.Cars.Interfaces
{
    public interface ICar
    {
        string Brand { get; }
        string Model { get; }
        int Year { get;  }
        int Id { get; }
    }
}

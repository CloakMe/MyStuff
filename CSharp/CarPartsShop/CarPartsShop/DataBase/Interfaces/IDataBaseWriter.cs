using CarPartsShop.Cars.Interfaces;
using CarPartsShop.CarParts.Interfaces;
using CarPartsShop.Shops.Interfaces;
using MySql.Data.MySqlClient;

namespace CarPartsShop.DataBase.Interfaces
{
    public interface IDataBaseWriter
    {
        void AddCar(ICar iCar);
        void AddCarPart(ICarPart iCarPart);
        void AssignPartToShop(string shopName, int carPartId, float prise);
    }
}

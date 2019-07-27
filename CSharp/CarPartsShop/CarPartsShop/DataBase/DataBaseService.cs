using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CarPartsShop.DataBase.Interfaces;
using MySql.Data.MySqlClient;
using CarPartsShop.Cars.Interfaces;
using CarPartsShop.Shops.Interfaces;
using CarPartsShop.Shops;
using CarPartsShop.Cars;
using CarPartsShop.CarParts.Interfaces;
using CarPartsShop.CarParts;

namespace CarPartsShop.DataBase
{
    public class DataBaseService : IDataBaseService
    {
        public DataBaseService(MySqlConnection mySqlConnection)
        {
            this.mySqlConnection = mySqlConnection;
            SelectCars();
            SelectCarsParts();
            SelectAllCarsParts();
        }

        MySqlConnection mySqlConnection;
        
        ICollection<ICar> cars = new List<ICar>();
        public ICollection<ICar> SelectCars()
        {
            string query = "select * from Cars";
            MySqlCommand commandDatabase = new MySqlCommand(query, mySqlConnection);
            MySqlDataReader reader;
            try
            {
                reader = commandDatabase.ExecuteReader();

                if (reader.HasRows)
                {
                    while (reader.Read())
                    {
                        int id = reader.GetInt32(0);
                        string brand = reader.GetString(1);
                        string model = reader.GetString(2);
                        int year = reader.GetInt32(3);
                        ICar car = new Car(brand, model, year, id);
                        cars.Add(car);
                    }
                    reader.Close();
                }
                else
                {
                    reader.Close();
                    return new List<ICar>();
                }

            }
            catch (Exception ex)
            {
                string f = ex.Message;
                return new List<ICar>();
            }
            return cars;
        }

        ICollection<ICarPart> carParts = new List<ICarPart>();
        public ICollection<ICarPart> SelectCarsParts()
        {
            string query = "select * from CarParts";
            MySqlCommand commandDatabase = new MySqlCommand(query, mySqlConnection);
            MySqlDataReader reader;
            try
            {
                reader = commandDatabase.ExecuteReader();

                if (reader.HasRows)
                {
                    while (reader.Read())
                    {
                        int id = reader.GetInt32(0);
                        string name = reader.GetString(1);
                        int carId = reader.GetInt32(2);
                        ICarPart carPartTest = carParts.FirstOrDefault(cp => cp.Name == name);
                        ICar iCar = cars.FirstOrDefault(c => c.Id == carId);
                        if (carPartTest == null)
                        {
                            ICarPart carPart = new CarPart(name, id);
                            carPart.SetPartForCar(iCar);
                            carParts.Add(carPart);
                        }
                        else
                        {
                            carPartTest.SetPartForCar(iCar);
                        }
                    }
                    reader.Close();
                }
                else
                {
                    reader.Close();
                    return carParts;
                }

            }
            catch (Exception ex)
            {
                string f = ex.Message;
                return carParts;
            }
            return carParts;
        }

        ICollection<ICarPart> allCarParts = new List<ICarPart>();
        public ICollection<ICarPart> SelectAllCarsParts()
        {
            string query = "select * from CarParts";
            MySqlCommand commandDatabase = new MySqlCommand(query, mySqlConnection);
            MySqlDataReader reader;
            try
            {
                reader = commandDatabase.ExecuteReader();

                if (reader.HasRows)
                {
                    while (reader.Read())
                    {
                        int id = reader.GetInt32(0);
                        string name = reader.GetString(1);
                        int carId = reader.GetInt32(2);
                        ICarPart carPart = new CarPart(name, id);
                        allCarParts.Add(carPart);
                    }
                    reader.Close();
                }
                else
                {
                    reader.Close();
                    return allCarParts;
                }

            }
            catch (Exception ex)
            {
                string f = ex.Message;
                return allCarParts;
            }

            return allCarParts;
        }

        ICollection<IShop> shops = new List<IShop>();
        public ICollection<IShop> SelectShops()
        {
            string query = "select * from Shops";
            MySqlCommand commandDatabase = new MySqlCommand(query, mySqlConnection);
            MySqlDataReader reader;
            try
            {
                reader = commandDatabase.ExecuteReader();

                if (reader.HasRows)
                {
                    while (reader.Read())
                    {
                        int id = reader.GetInt32(0);
                        string shopName = reader.GetString(1);
                        int carPartId = reader.GetInt32(2);
                        double prise = reader.GetDouble(3);

                        IShop shopTest = shops.FirstOrDefault(sh => sh.Name == shopName);
                        ICarPart iCarPart = allCarParts.FirstOrDefault(cp => cp.Id == carPartId);
                        ICarPart iCarPartSingle = carParts.FirstOrDefault(cp => cp.Name == iCarPart.Name);
                        if (shopTest == null)
                        {
                            IShop shop = new Shop(shopName);
                            shop.AddCarPartWithPrise(iCarPartSingle, prise);
                            shops.Add(shop);
                        }
                        else
                        {
                            shopTest.AddCarPartWithPrise(iCarPartSingle, prise);
                        }
                    }
                    reader.Close();
                }
                else
                {
                    reader.Close();
                    return shops;
                }

            }
            catch (Exception ex)
            {
                // Show any error message.
                string f = ex.Message;
                return shops;
            }
            return shops;
        }

    }
}

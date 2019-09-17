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
using System.Windows;

namespace CarPartsShop.DataBase
{
    public class DataBaseReader : IDataBaseReader
    {
        public DataBaseReader(MySqlConnection mySqlConnection)
        {
            this.mySqlConnection = mySqlConnection;
            SelectCars();
            SelectCarsParts();
            SelectAllCarsParts();
        }

        MySqlConnection mySqlConnection;
        
        public ICollection<ICar> GetCars
        {
            get
            {
                ICollection<ICar> carsCopy = new List<ICar>();
                foreach (ICar iCar in cars)
                    carsCopy.Add(iCar);
                return carsCopy;
            }
        }

        public ICollection<ICarPart> GetCarPartsUnique
        {
            get
            {
                ICollection<ICarPart> carsPartsCopy = new List<ICarPart>();
                foreach (ICarPart iCarPart in carParts)
                    carsPartsCopy.Add(iCarPart);
                return carsPartsCopy;
            }
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
                MessageBox.Show("Could not load car shop from the database! " + ex.Message);
                string f2 = ex.Message;
                return shops;
            }
            return shops;
        }

        ICollection<ICar> cars = new List<ICar>();
        private ICollection<ICar> SelectCars()
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
                MessageBox.Show("Could not load car model, brand and year from the database! " + ex.Message);
                string f2 = ex.Message;
                return new List<ICar>();
            }
            return cars;
        }

        ICollection<ICarPart> carParts = new List<ICarPart>();
        private ICollection<ICarPart> SelectCarsParts()
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
                            carPart.Ids.Add(id);
                            carParts.Add(carPart);
                        }
                        else
                        {
                            carPartTest.SetPartForCar(iCar);
                            carPartTest.Ids.Add(id);
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
                MessageBox.Show("Could not load car part from the database! " + ex.Message);
                string f2 = ex.Message;
                return carParts;
            }
            return carParts;
        }

        ICollection<ICarPart> allCarParts = new List<ICarPart>();
        private ICollection<ICarPart> SelectAllCarsParts()
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
                MessageBox.Show("Could not load car part (2) from the database! " + ex.Message);
                string f2 = ex.Message;
                return allCarParts;
            }

            return allCarParts;
        }

    }
}

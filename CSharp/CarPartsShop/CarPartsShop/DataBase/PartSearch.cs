using CarPartsShop.CarParts;
using CarPartsShop.CarParts.Interfaces;
using CarPartsShop.Cars.Interfaces;
using CarPartsShop.DataBase.Interfaces;
using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CarPartsShop.Common;

namespace CarPartsShop.DataBase
{
    public class PartSearch : IPartSearch
    {
        public PartSearch(MySqlConnection mySqlConnection, IDataBaseService dbs)
        {
            this.mySqlConnection = mySqlConnection;
            this.dbs = dbs;
        }
        IDataBaseService dbs;
        MySqlConnection mySqlConnection;

        private ICarPart SelectCarPartByName(string partName)
        {
            ICollection < ICarPart > carParts = new List<ICarPart>();
            string query = "select * from CarParts where name = \"" + partName + "\"";
            MySqlCommand commandDatabase = new MySqlCommand(query, mySqlConnection);
            MySqlDataReader reader;
            ICollection<ICar> cars = dbs.GetCars;
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
                        ICarPart carPartTest = carParts.FirstOrDefault(cp => cp.Name == partName);
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
                    return carParts.FirstOrDefault();
                }

            }
            catch (Exception ex)
            {
                string f = ex.Message;
                return carParts.FirstOrDefault();
            }
            return carParts.FirstOrDefault();
        }

        public ICollection<ShopItem> SelectCarPartInShops(string partName)
        {
            ICarPart iCarPart = SelectCarPartByName(partName);

            ICollection<ShopItem> items = new List<ShopItem>();
            if (iCarPart == null)
                return items;

            string query = "select * from Shops where carPartId =" + iCarPart.Id;
            MySqlCommand commandDatabase = new MySqlCommand(query, mySqlConnection);
            MySqlDataReader reader;
            ICollection<ICar> cars = dbs.GetCars;
            try
            {
                reader = commandDatabase.ExecuteReader();

                if (reader.HasRows)
                {
                    while (reader.Read())
                    {
                        ShopItem item = new ShopItem();
                        int id = reader.GetInt32(0);
                        item.ShopName = reader.GetString(1);
                        int carPartId = reader.GetInt32(2);
                        item.Prise = reader.GetDouble(3).ToString();
                        item.PartName = iCarPart.Name;
                        items.Add(item);
                    }
                    reader.Close();
                }
                else
                {
                    reader.Close();
                    return items;
                }

            }
            catch (Exception ex)
            {
                string f = ex.Message;
                return items;
            }
            return items;
        }

    }
}

using CarPartsShop.Cars.Interfaces;
using CarPartsShop.CarParts.Interfaces;
using CarPartsShop.Shops.Interfaces;
using MySql.Data.MySqlClient;
using CarPartsShop.DataBase.Interfaces;
using System;
using CarPartsShop.Cars;
using System.Collections.Generic;

namespace CarPartsShop.DataBase
{
    public class MyDataBase : IDataBase
    {
        public MyDataBase(string dataBase, string server, uint port, string userID, string pass)
        {
            MySqlConnectionStringBuilder myBuilder = new MySqlConnectionStringBuilder();
            myBuilder.Database = dataBase;
            myBuilder.Server = server;
            myBuilder.Port = port;
            myBuilder.UserID = userID;
            myBuilder.Password = pass;

            MySQLConn = new MySqlConnection(myBuilder.ConnectionString);
            // Open the database
            MySQLConn.Open();
        }

        MySqlConnection MySQLConn;

        public void AddCar(ICar iCar)
        {
            string query = "insert into Cars (brand, model, `year`) values ( \'" + iCar.Brand + "\', \'" + iCar.Model + "\', \'" + iCar.Year.ToString() + "\') ";
            MySqlCommand commandDatabase = new MySqlCommand(query, MySQLConn);
            commandDatabase.CommandTimeout = 15;
            try
            {
                int result = commandDatabase.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                // Show any error message.
                string f = ex.Message;
            }
        }

        public void AddCarPart(ICarPart iCarPart)
        {
            foreach (ICar iCar in iCarPart.Cars)
            {
                string query = "insert into CarParts (name, carID) values (\'" + iCarPart.Name + "\', \'" + iCar.Id + "\') ";
                MySqlCommand commandDatabase = new MySqlCommand(query, MySQLConn);
                commandDatabase.CommandTimeout = 15;
                try
                {
                    commandDatabase.ExecuteNonQuery();
                }
                catch (Exception ex)
                {
                    // Show any error message.
                    string f  = ex.Message;
                }
            }
            
        }

        public void AssignPartToShop(string shopName, int carPartId, float prise)
        {
            string query = "insert into CarShop (shopName, carPartID, prise) values ( \'" + shopName + "\', \'" + 
                carPartId.ToString() + "\', \'" + prise.ToString() + "\') ";
            MySqlCommand commandDatabase = new MySqlCommand(query, MySQLConn);
            commandDatabase.CommandTimeout = 15;
            try
            {
                int result = commandDatabase.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                // Show any error message.
                string f = ex.Message;
            }
        }

        private List<ICar> GetCars()
        {
            string query = "select * Cars";
            MySqlCommand commandDatabase = new MySqlCommand(query, MySQLConn);
            MySqlDataReader reader;
            List<ICar> cars = new List<ICar>();
            try
            {
                // Execute the query
                reader = commandDatabase.ExecuteReader();

                // All succesfully executed, now do something

                // IMPORTANT : 
                // If your query returns result, use the following processor :

                if (reader.HasRows)
                {
                    while (reader.Read())
                    {
                        // As our database, the array will contain : ID 0, FIRST_NAME 1,LAST_NAME 2, ADDRESS 3
                        // Do something with every received database ROW
                        int id = reader.GetInt32(0);
                        string brand = reader.GetString(1);
                        string model = reader.GetString(2);
                        int year = reader.GetInt32(3);
                        ICar car = new Car(brand, model, year, id);
                        cars.Add(car);
                    }
                }
                else
                {
                    return new List<ICar>();
                }

            }
            catch (Exception ex)
            {
                // Show any error message.
                string f = ex.Message;
                return new List<ICar>();
            }
            return cars;
            
        }

        ~MyDataBase()
        {
            MySQLConn.Close();
        }
    }
}

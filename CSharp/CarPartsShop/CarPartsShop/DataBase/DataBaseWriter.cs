using CarPartsShop.Cars.Interfaces;
using CarPartsShop.CarParts.Interfaces;
using CarPartsShop.Shops.Interfaces;
using MySql.Data.MySqlClient;
using CarPartsShop.DataBase.Interfaces;
using System;
using CarPartsShop.Cars;
using System.Collections.Generic;
using System.Windows;

namespace CarPartsShop.DataBase
{
    public class DataBaseWriter : IDataBaseWriter
    {
        public DataBaseWriter(MySqlConnection mySqlConnection)
        {
            this.mySqlConnection = mySqlConnection;
        }

        MySqlConnection mySqlConnection;

        public void AddCar(ICar iCar)
        {
            string query = "insert into Cars (brand, model, `year`) values ( \'" + iCar.Brand + "\', \'" + iCar.Model + "\', \'" + iCar.Year.ToString() + "\') ";
            MySqlCommand commandDatabase = new MySqlCommand(query, mySqlConnection);
            commandDatabase.CommandTimeout = 15;
            try
            {
                int result = commandDatabase.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                // Show any error message.
                MessageBox.Show("Could not save car model, brand and year to the database! " + ex.Message);
                string f2 = ex.Message;
            }
        }

        public void AddCarPart(ICarPart iCarPart)
        {
            foreach (ICar iCar in iCarPart.Cars)
            {
                string query = "insert into CarParts (name, carId) values (\'" + iCarPart.Name + "\', \'" + iCar.Id + "\') ";
                MySqlCommand commandDatabase = new MySqlCommand(query, mySqlConnection);
                commandDatabase.CommandTimeout = 15;
                try
                {
                    commandDatabase.ExecuteNonQuery();
                }
                catch (Exception ex)
                {
                    // Show any error message.
                    MessageBox.Show("Could not save car part to the database! " + ex.Message);
                    string f2  = ex.Message;
                }
            }
            
        }

        public void AssignPartToShop(string shopName, int carPartId, float prise)
        {
            string query = "insert into Shops (shopName, carPartId, prise) values ( \'" + shopName + "\', " + 
                carPartId.ToString() + ", \'" + prise.ToString() + "\') ";
            MySqlCommand commandDatabase = new MySqlCommand(query, mySqlConnection);
            commandDatabase.CommandTimeout = 15;
            try
            {
                int result = commandDatabase.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                // Show any error message.
                MessageBox.Show("Could not assign car part to given shop in the database! " + ex.Message);
                string f2 = ex.Message;
            }
        }

        ~DataBaseWriter()
        {
            mySqlConnection.Close();
        }
    }
}

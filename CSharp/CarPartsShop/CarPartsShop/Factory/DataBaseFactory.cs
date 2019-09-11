using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CarPartsShop.DataBase.Interfaces;
using CarPartsShop.DataBase;
using MySql.Data.MySqlClient;

namespace CarPartsShop.Factory
{
    public static class DataBaseFactory
    {
        private static readonly string server = "remotemysql.com";
        private static readonly string dataBase = "reBGwYb8G1";
        private static readonly uint port = 3306;
        private static readonly string userID = "reBGwYb8G1";
        private static readonly string pass = "hIuP7fYVnb";

        static DataBaseFactory()
        {
            MySqlConnectionStringBuilder myBuilder = new MySqlConnectionStringBuilder();
            myBuilder.Database = dataBase;
            myBuilder.Server = server;
            myBuilder.Port = port;
            myBuilder.UserID = userID;
            myBuilder.Password = pass;

            mySqlConnection = new MySqlConnection(myBuilder.ConnectionString);
            // Open the database
            mySqlConnection.Open();

            db = new MyDataBase(mySqlConnection);
            dbs = new DataBaseService(mySqlConnection);

        }
        private static MySqlConnection mySqlConnection;

        private static IDataBaseWriter db;
        public static IDataBaseWriter GenerateDadaBase()
        {
            return db;
        }

        private static IDataBaseReader dbs;
        public static IDataBaseReader GenerateDadaBaseService()
        {
            return dbs;
        }

        public static IPartSearch GeneratePartSearch()
        {
            IPartSearch partSearch = new PartSearch(mySqlConnection, dbs);
            return partSearch;
        }
    }
}

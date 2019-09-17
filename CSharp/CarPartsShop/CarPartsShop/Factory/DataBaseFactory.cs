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

            dbWriter = new DataBaseWriter(mySqlConnection);
            dbReader = new DataBaseReader(mySqlConnection);

        }
        private static MySqlConnection mySqlConnection;

        private static IDataBaseWriter dbWriter;
        public static IDataBaseWriter GetDBWriterInstance()
        {
            return dbWriter;
        }

        private static IDataBaseReader dbReader;
        public static IDataBaseReader GetDBReaderInstance()
        {
            return dbReader;
        }

        public static IPartSearch GeneratePartSearch()
        {
            IPartSearch partSearch = new PartSearch(mySqlConnection, dbReader);
            return partSearch;
        }
    }
}

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
        private static readonly string server = "sql7.freesqldatabase.com";
        private static readonly string dataBase = "sql7299547";
        private static readonly uint port = 3306;
        private static readonly string userID = "sql7299547";
        private static readonly string pass = "pAxwgTkKaS";

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

        private static IDataBase db;
        public static IDataBase GenerateDadaBase()
        {
            return db;
        }

        private static IDataBaseService dbs;
        public static IDataBaseService GenerateDadaBaseService()
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

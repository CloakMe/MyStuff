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
        }
        private static MySqlConnection mySqlConnection;

        public static IDataBase GenerateDadaBase()
        {
            IDataBase db = new MyDataBase(mySqlConnection);
            return db;
        }

        public static IDataBaseService GenerateDadaBaseService()
        {
            IDataBaseService dbs = new DataBaseService(mySqlConnection);
            return dbs;
        }
    }
}

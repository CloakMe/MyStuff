using System.Windows;
using System;
using CarPartsShop.DataBase.Interfaces;
using CarPartsShop.DataBase;
using CarPartsShop.Cars;
using System.ComponentModel;
using CarPartsShop.Shops.Interfaces;
using CarPartsShop.Shops;
using CarPartsShop.Cars.Interfaces;
using CarPartsShop.CarParts.Interfaces;
using CarPartsShop.CarParts;

namespace CarPartsShop
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        private static readonly string server = "sql7.freesqldatabase.com";
        private static readonly string dataBase = "sql7299547";
        private static readonly uint port = 3306;
        private static readonly string userID = "sql7299547";
        private static readonly string pass = "pAxwgTkKaS";

        public MainWindow()
        {
            //InitializeComponent();
            db = new MyDataBase(dataBase, server, port, userID, pass);
            shop = new Shop("Slavejkov");

            //db.AddCar(new Car("Ford", "Focus", 2000));
            //db.AddCar(new Car("Ford", "Focus", 1999));
            //db.AddCar(new Car("Ford", "Focus", 2001));
            //db.AddCar(new Car("Ford", "Fiesta", 2003));
        }

        private IDataBase db;

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private IShop shop;

        public IShop Shop
        {
            get { return shop; }
            set
            {
                if (value.Name != shop.Name || 
                    value.CarPartsWithPrise.Count != shop.CarPartsWithPrise.Count)
                {
                    shop = value;
                    OnPropertyChanged("Shop");
                }
            }
        }

        private void OnAddCarMenuClick(object sender, RoutedEventArgs e)
        {
            AddCarForm.Visibility = Visibility.Visible;
            AddCarPartForm.Visibility = Visibility.Collapsed;
            AddPartToShopForm.Visibility = Visibility.Collapsed;
        }

        private void OnAddCarPartMenuClick(object sender, RoutedEventArgs e)
        {
            AddCarPartForm.Visibility = Visibility.Visible;
            AddCarForm.Visibility = Visibility.Collapsed;
            AddPartToShopForm.Visibility = Visibility.Collapsed;
        }

        private void OnAddShopMenuClick(object sender, RoutedEventArgs e)
        {
            AddCarPartForm.Visibility = Visibility.Collapsed;
            AddCarForm.Visibility = Visibility.Collapsed;
            AddPartToShopForm.Visibility = Visibility.Visible;
        }

        private void OnAddCarClick(object sender, RoutedEventArgs e)
        {
            ICar iCar = new Car(CarBrand.Text, CarModel.Text, Int32.Parse(CarYear.Text) );
            db.AddCar(iCar);
        }

        private void OnAddCarPartClick(object sender, RoutedEventArgs e)
        {
            ICarPart iCarPart = new CarPart(PartName.Text);
            ICar iCar = new Car("", "", 0, Int32.Parse(CarID.Text));
            iCarPart.SetPartForCar(iCar);
            db.AddCarPart(iCarPart);
        }

        private void OnAssignPartToShopClick(object sender, RoutedEventArgs e)
        {
            db.AssignPartToShop(ShopName.Text, Int32.Parse(PartID.Text), float.Parse(PartPrise.Text) );
        }
    }
    
}

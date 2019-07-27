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
using CarPartsShop.Factory;
using System.Collections.Generic;

namespace CarPartsShop
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            db = DataBaseFactory.GenerateDadaBase();

            bool breakPoint = true;
        }

        private IDataBase db;

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

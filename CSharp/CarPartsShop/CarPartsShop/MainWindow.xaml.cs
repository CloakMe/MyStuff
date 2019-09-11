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
using CarPartsShop.UIControls;
using CarPartsShop.Common.Interfaces;
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
            dbWriter = DataBaseFactory.GetDBWriterInstance();            

            bool breakPoint = true;
        }

        private IDataBaseWriter dbWriter;
        private IDataBaseReader dbReader;

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
            
            IDataBaseReader dbReader = DataBaseFactory.GetDBReaderInstance();
            ICollection<IName> cars = new List<IName>();
            foreach (ICar iCar in dbReader.GetCars)
            {
                cars.Add(iCar as IName);
            }
            myCarCombo.SetItems(cars);
        }

        private void OnAsignPartToShopMenuClick(object sender, RoutedEventArgs e)
        {
            AddCarPartForm.Visibility = Visibility.Collapsed;
            AddCarForm.Visibility = Visibility.Collapsed;
            AddPartToShopForm.Visibility = Visibility.Visible;

            IDataBaseReader dbReader = DataBaseFactory.GetDBReaderInstance();
            ICollection<IName> carParts = new List<IName>();
            foreach (ICarPart iCarPart in dbReader.GetCarPartsUnique)
            {
                carParts.Add(iCarPart as IName);
            }
            myCarPartCombo.SetItems(carParts);
        }

        private void OnAddCarClick(object sender, RoutedEventArgs e)
        {
            ICar iCar = new Car(CarBrand.Text, CarModel.Text, Int32.Parse(CarYear.Text) );
            dbWriter.AddCar(iCar);
        }

        private void OnAddCarPartClick(object sender, RoutedEventArgs e)
        {
            ICarPart iCarPart = new CarPart(PartName.Text);
            ICar iCar = myCarCombo.GetSelectedItem() as ICar;
            if (iCar == null)
                return;
            iCarPart.SetPartForCar(iCar);
            dbWriter.AddCarPart(iCarPart);

        }

        private void OnAssignPartToShopClick(object sender, RoutedEventArgs e)
        {
            ICarPart iCarPart = myCarPartCombo.GetSelectedItem() as ICarPart;
            if (iCarPart == null)
                return;
            foreach(int id in iCarPart.Ids)
                dbWriter.AssignPartToShop(ShopName.Text, id, float.Parse(PartPrise.Text));
        }

        private void OnGoClick(object sender, RoutedEventArgs e)
        {
            string searchPart = SearchBox.Text;
            myListvu.SetItems(searchPart, NothingFound);
        }
    }
    
}

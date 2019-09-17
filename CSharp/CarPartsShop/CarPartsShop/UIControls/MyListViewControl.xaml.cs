using CarPartsShop.CarParts.Interfaces;
using CarPartsShop.DataBase.Interfaces;
using CarPartsShop.Factory;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using CarPartsShop.Common;

namespace CarPartsShop.UIControls
{
    /// <summary>
    /// Interaction logic for MyListViewControl.xaml
    /// </summary>
    public partial class MyListViewControl : UserControl, INotifyPropertyChanged
    {
        public MyListViewControl()
        {
            InitializeComponent();

            myListView.ItemsSource = items;
        }

        public event PropertyChangedEventHandler PropertyChanged;
        private void OnPropertyChanged(string propertyname)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyname));
            }
        }

        ObservableCollection<ShopItem> items = new ObservableCollection<ShopItem>();
        public ObservableCollection<ShopItem> Items {
            get { return items; }
            set
            {
                items = value;
                // Call OnPropertyChanged whenever the property is updated
                OnPropertyChanged("Items");
            }
        } 

        public void SetItems(string partName, FrameworkElement nothingFound)
        {
            items.Clear();
            IPartSearch partSearch = DataBaseFactory.GeneratePartSearch();
            ICollection<ShopItem> queryItems = partSearch.SelectCarPartInShops(partName);
            foreach (ShopItem liItem in queryItems)
            {
                items.Add(liItem);
            }

            if (items.Count == 0)
                nothingFound.Visibility = Visibility.Visible;
            else
                nothingFound.Visibility = Visibility.Hidden;

            Items = items;
        }

    }


}

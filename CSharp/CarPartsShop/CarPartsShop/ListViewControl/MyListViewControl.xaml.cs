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
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using CarPartsShop.Common;

namespace CarPartsShop.ListViewControl
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

        ObservableCollection<ListItem> items = new ObservableCollection<ListItem>();
        public ObservableCollection<ListItem> Items {
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
            IPartSearch partSearch = DataBaseFactory.GeneratePartSearch();
            ICollection<ListItemS> queryItems = partSearch.SelectCarPartInShops(partName);
            items.Clear();
            foreach (ListItemS liItem in queryItems)
            {
                //string partDescription = partName;
                ListItem li = new ListItem();
                li.PartName = liItem.PartName;
                li.Prise = liItem.Prise;
                li.ShopName = liItem.ShopName;
                items.Add(li);
            }

            if (items.Count == 0)
                nothingFound.Visibility = Visibility.Visible;
            else
                nothingFound.Visibility = Visibility.Hidden;

            Items = items;
        }

    }

    public class ListItem
    {
        public ListItem()
        {

        }

        public string ShopName { get; set; }
        public string PartName { get; set; }
        public string Prise { get; set; }
    }

}

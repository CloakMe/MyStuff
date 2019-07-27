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
            ListItem li = new ListItem();
            li.PartName = "breaks";
            li.Prise = "46.79";
            li.CarName = "Nissan";
            items.Add(li);
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

        public void SetItems(string partName)
        {
            IPartSearch partSearch = DataBaseFactory.GeneratePartSearch();
            ICollection<ICarPart> iCarParts = partSearch.SelectCarPartsByName(partName);
            foreach (ICarPart iCarPart in iCarParts)
            {
                //string partDescription = partName;
                ListItem li = new ListItem();
                li.PartName = "hood";
                li.Prise = "46.79";
                li.CarName = "Nissan";
                items.Add(li);
            }

            Items = items;
        }

    }

    public class ListItem
    {
        public ListItem()
        {

        }

        public string CarName { get; set; }
        public string PartName { get; set; }
        public string Prise { get; set; }
    }

}

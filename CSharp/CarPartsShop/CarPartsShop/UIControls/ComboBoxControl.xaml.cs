using System;
using System.Collections.Generic;
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
using System.ComponentModel;
using CarPartsShop.Cars.Interfaces;
using System.Collections.ObjectModel;
using CarPartsShop.Common.Interfaces;

namespace CarPartsShop.UIControls
{
    /// <summary>
    /// Interaction logic for ComboBoxControl.xaml
    /// </summary>
    public partial class ComboBoxControl : UserControl, INotifyPropertyChanged
    {
        public ComboBoxControl()
        {
            InitializeComponent();

            carsCombo.ItemsSource = items;
        }

        public event PropertyChangedEventHandler PropertyChanged;
        private void OnPropertyChanged(string propertyname)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyname));
            }
        }

        ObservableCollection<IName> items = new ObservableCollection<IName>();
        public ObservableCollection<IName> Items
        {
            get { return items; }
            set
            {
                items = value;
                // Call OnPropertyChanged whenever the property is updated
                OnPropertyChanged("Items");
            }
        }

        public void SetItems(ICollection<IName> itemsIn)
        {
            items.Clear();

            foreach (IName liItem in itemsIn)
            {
                items.Add(liItem);
            }

            Items = items;
        }

        public IName GetSelectedItem()
        {
            if (carsCombo.SelectedItem != null)
                return (carsCombo.SelectedItem as IName);
            else
                return null;
        }
    }
}

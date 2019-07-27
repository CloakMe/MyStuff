using CarPartsShop.CarParts.Interfaces;
using CarPartsShop.DataBase.Interfaces;
using CarPartsShop.Factory;
using CarPartsShop.Shops.Interfaces;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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

namespace CarPartsShop.TreeViewControl
{
    /// <summary>
    /// Interaction logic for MyTreeView.xaml
    /// </summary>
    public partial class MyTreeView : UserControl
    {
        public MyTreeView()
        {
            InitializeComponent();
            IDataBaseService dbs = DataBaseFactory.GenerateDadaBaseService();
            ICollection<IShop> shops = dbs.SelectShops();

            MenuItem root = new MenuItem() { Title = "Shops Menu" };
            foreach (IShop iShop in shops)
            {
                MenuItem childItem = new MenuItem() { Title = iShop.Name };
                foreach (KeyValuePair<ICarPart, double> iCarPartWithPrise in iShop.CarPartsWithPrise)
                {
                    MenuItem subChildItem = new MenuItem()
                    {
                        Title = iCarPartWithPrise.Key.Name + "  " + iCarPartWithPrise.Value.ToString(),
                        Prise = iCarPartWithPrise.Value
                    };
                    childItem.Items.Add(subChildItem);
                }
                root.Items.Add(childItem);
            }
            trvMenu.Items.Add(root);
        }

    }

    public class MenuItem
    {
        public MenuItem()
        {
            this.Items = new ObservableCollection<MenuItem>();
        }

        public string Title { get; set; }

        public double Prise { get; set; }

        public ObservableCollection<MenuItem> Items { get; set; }
    }
}

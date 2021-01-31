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
using TwinCAT.Ads;
using System.ComponentModel;

namespace WpfApp2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        public MainWindow()
        {
            InitializeComponent();
            _tcClient = new TcAdsClient();
            adsReadStream = new AdsStream(4);
            adsWriteStream = new AdsStream(4);
            DataContext = this;
        }

        private TcAdsClient _tcClient;
        private AdsStream adsWriteStream;
        private AdsStream adsReadStream;


        private void MainWindow_Load(object sender, EventArgs e)
        {

        }
        public int PortValue { get; set; }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                _tcClient.ReadWrite(0x1, 0x1, adsReadStream, adsWriteStream);
                byte[] dataBuffer = adsReadStream.ToArray();
                Box.Text = "Counter started value = " + BitConverter.ToUInt32(dataBuffer, 0);
                
            }

            catch (Exception err)
            {
                MessageBox.Show(err.Message);
            }


        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            Console.WriteLine("Connect is clicked");
            AmsAddress serverAddress = null;
            //int num1 = int.Parse(Port.Text);
            MessageBox.Show(Port.Text);

            try
            {
                // check if port is a hex value
                if (Port.Text.StartsWith(("0x")) || Port.Text.StartsWith(("0X")))
                {
                    string sHexValue = Port.Text.Substring(2);
                    serverAddress = new AmsAddress(netId.Text, Int32.Parse(sHexValue, System.Globalization.NumberStyles.HexNumber));
                }
                // interpret as dec value
                else
                {
                    serverAddress = new AmsAddress(netId.ToString(), Int32.Parse(Port.Text));
                }

            }
            catch
            {
                MessageBox.Show("Invalid AMS NetId or Ams port");
                return;
            }

            try
            {
                _tcClient.Connect(serverAddress.NetId, serverAddress.Port);
                Box.Text = "Client port " + _tcClient.ClientAddress.Port + " opened";
                //lbOutput.SelectedIndex = lbOutput.Items.Count - 1;

            }
                catch
            {
                MessageBox.Show("Could not connect client");
            }
        }

        private void Button_Read(object sender, RoutedEventArgs e)
        {
            try
            {
                _tcClient.ReadWrite(0x1, 0x2, adsReadStream, adsWriteStream);
                byte[] dataBuffer = adsReadStream.ToArray();
                Box.Text = "Counter = " + BitConverter.ToUInt32(dataBuffer, 0);

            }

            catch (Exception err)
            {
                MessageBox.Show(err.Message);
            }
        }

        string overwrite;

        public string Overwrite

        {

            get { return overwrite; }

            set

            {

                if (overwrite == value)

                    return;

                overwrite = value;

                if (PropertyChanged != null)

                    SendPropertyChanged("Name");

            }

        }

        private void SendPropertyChanged(string propertyName)
        {
            PropertyChangedEventHandler handler = this.PropertyChanged;
            if (handler != null)
            {
                var e = new PropertyChangedEventArgs(propertyName);
                this.PropertyChanged(this, e);
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void Overwrite_Clicked(object sender, RoutedEventArgs e)
        {
            try
            {
                AdsBinaryWriter binWriter = new AdsBinaryWriter(adsWriteStream);
                adsWriteStream.Position = 0;

                binWriter.Write(uint.Parse(Overwrite));
                _tcClient.ReadWrite(0x3, 0x1, adsReadStream, adsWriteStream);
                byte[] dataBuffer = adsReadStream.ToArray();
                Box.Text = "Counter overwritten with Value = " + BitConverter.ToUInt32(dataBuffer, 0);

            }

            catch (Exception err)
            {
                MessageBox.Show(err.Message);
            }
        }
    }


}


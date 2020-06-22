using System;
using System.Windows.Forms;
using Command;
using Transmission;

namespace WindowsApplication
{
    public partial class aHandControllerForm : Form
    {
        private Encoder CommandEncoder;
        private ITransmitter CommandTransmitter;

        public aHandControllerForm()
        {
            InitializeComponent();
            this.CommandEncoder = new Encoder();
            this.CommandTransmitter = new SerialTransmitter();
        }

        private void aButtonExtend_Click(object sender, EventArgs e)
        {

        }

        private void aButtonContract_Click(object sender, EventArgs e)
        {

        }

        private void aButtonConnect_Click(object sender, EventArgs e)
        {
            // Make sure port and baud rate are selected
            if (aListBaudRates.SelectedItem == null || aListPortNames.SelectedItem == null)
            {
                aTextOutput.AppendText("Please select port name and baud rate." + Environment.NewLine);
                return;
            }

            // Try to connect to serial transmitter
            if (this.CommandTransmitter is SerialTransmitter)
            {
                SerialTransmitter serialTransmitter = this.CommandTransmitter as SerialTransmitter;
                string portName = (string) aListPortNames.SelectedItem;
                int baudRate = int.Parse((string)aListBaudRates.SelectedItem);

                if (serialTransmitter.OpenSerialPort(portName, baudRate))
                {
                    aTextOutput.AppendText("Successfully opened serial port " + portName + " with baud rate " + baudRate + "." + Environment.NewLine);
                }
                else
                {
                    aTextOutput.AppendText("Failed to open serial port " + portName + " with baud rate " + baudRate + "." + Environment.NewLine);
                }
            }
        }

        private void aHandControllerForm_Load(object sender, EventArgs e)
        {
            // Initialize lists of available port names and baud rates
            if (this.CommandTransmitter is SerialTransmitter)
            {
                SerialTransmitter serialTransmitter = this.CommandTransmitter as SerialTransmitter;
                string[] portNames = serialTransmitter.PortNames;
                string[] baudRates = serialTransmitter.BaudRates;
                foreach (string portName in portNames)
                {
                    aListPortNames.Items.Add(portName);
                }
                foreach (string baudRate in baudRates)
                {
                    aListBaudRates.Items.Add(baudRate);
                }
            }
        }

        private void aHandControllerForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (this.CommandTransmitter is SerialTransmitter)
            {
                SerialTransmitter serialTransmitter = this.CommandTransmitter as SerialTransmitter;
                serialTransmitter.CloseSerialPort();
            }
        }

        // Slider to specify speed of contraction (1-3), button to contract, button to extend
        // Dropdown that lists all available ports, dropdown that lists available baud rates, buttons to select
        // Add threads to serial transmitter for reading and writing
        // Add selection menu for form to select type of communication
    }
}

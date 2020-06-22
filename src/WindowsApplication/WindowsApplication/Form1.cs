using System;
using System.Windows.Forms;
using Commands;
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

        #region General Form Events

        private void aHandControllerForm_Load(object sender, EventArgs e)
        {
            this.ReadConnectionConfig();
        }

        private void aHandControllerForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (this.CommandTransmitter is SerialTransmitter)
            {
                SerialTransmitter serialTransmitter = this.CommandTransmitter as SerialTransmitter;
                serialTransmitter.CloseSerialPort();
            }
        }

        #endregion

        #region Connection Events

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
                string portName = (string)aListPortNames.SelectedItem;
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

        private void aRefreshButton_Click(object sender, EventArgs e)
        {
            this.ReadConnectionConfig();
        }

        /// <summary>
        /// Reads connection configuration into form for user selection.
        /// </summary>
        private void ReadConnectionConfig()
        {
            // Initialize lists of available port names and baud rates
            if (this.CommandTransmitter is SerialTransmitter)
            {
                SerialTransmitter serialTransmitter = this.CommandTransmitter as SerialTransmitter;
                string[] portNames = serialTransmitter.PortNames;
                string[] baudRates = serialTransmitter.BaudRates;

                aListPortNames.Items.Clear();
                foreach (string portName in portNames)
                {
                    aListPortNames.Items.Add(portName);
                }

                aListBaudRates.Items.Clear();
                foreach (string baudRate in baudRates)
                {
                    aListBaudRates.Items.Add(baudRate);
                }
            }
        }

        #endregion

        #region Movement Control Events

        private void aButtonExtend_Click(object sender, EventArgs e)
        {
            string speed = aTrackBarSpeed.Value.ToString();
            this.SendCommand(new Command(CommandTypeEnum.FINGER_ALL, CommandActionEnum.EXTEND, speed));
        }

        private void aButtonContract_Click(object sender, EventArgs e)
        {
            string speed = aTrackBarSpeed.Value.ToString();
            this.SendCommand(new Command(CommandTypeEnum.FINGER_ALL, CommandActionEnum.CONTRACT, speed));
        }

        private void aButtonStop_Click(object sender, EventArgs e)
        {
            this.SendCommand(new Command(CommandTypeEnum.FINGER_ALL, CommandActionEnum.STOP));
        }

        /// <summary>
        /// Encodes and sends provided command to microcontroller.
        /// </summary>
        /// <param name="command"></param>
        private void SendCommand(Command command)
        {
            string encodedCommand = this.CommandEncoder.EncodeCommand(command);
            if (this.CommandTransmitter is SerialTransmitter)
            {
                SerialTransmitter serialTransmitter = this.CommandTransmitter as SerialTransmitter;

                if (serialTransmitter.Send(encodedCommand))
                {
                    aTextOutput.AppendText("Successfully send command " + encodedCommand + "." + Environment.NewLine);
                }
                else
                {
                    aTextOutput.AppendText("Failed to send command " + encodedCommand + "." + Environment.NewLine);
                }
            }
        }

        #endregion

        // Slider to specify speed of contraction (1-3), button to contract, button to extend
        // Add threads to serial transmitter for reading and writing
        // Add selection menu for form to select type of communication
    }
}

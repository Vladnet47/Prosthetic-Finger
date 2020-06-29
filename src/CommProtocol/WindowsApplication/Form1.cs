using System;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;
using Commands;
using Transmission;

namespace WindowsApplication
{
    public partial class aHandControllerForm : Form
    {
        private Encoder CommandEncoder;
        private ITransmitter CommandTransmitter;
        private int ContinuousRotationCommandFrequency;

        public aHandControllerForm()
        {
            InitializeComponent();
            this.CommandEncoder = new Encoder();
            this.CommandTransmitter = new SerialTransmitter();
            this.ContinuousRotationCommandFrequency = 500;
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
                serialTransmitter.Disconnect();
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

                string message = serialTransmitter.Connect(portName, baudRate);
                aTextOutput.AppendText(message);
            }
        }

        private void aButtonDisconnect_Click(object sender, EventArgs e)
        {
            if (this.CommandTransmitter is SerialTransmitter)
            {
                SerialTransmitter serialTransmitter = this.CommandTransmitter as SerialTransmitter;
                string message = serialTransmitter.Disconnect();
                aTextOutput.AppendText(message);
            }
        }

        private void aRefreshButton_Click(object sender, EventArgs e)
        {
            if (this.CommandTransmitter is SerialTransmitter)
            {
                SerialTransmitter serialTransmitter = this.CommandTransmitter as SerialTransmitter;
                string message = serialTransmitter.Disconnect();
                aTextOutput.AppendText(message);
                this.ReadConnectionConfig();
            }
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
                    if (!aListPortNames.Items.Contains(portName))
                    {
                        aListPortNames.Items.Add(portName);
                    }
                }

                aListBaudRates.Items.Clear();
                foreach (string baudRate in baudRates)
                {
                    if (!aListBaudRates.Items.Contains(baudRate))
                    {
                        aListBaudRates.Items.Add(baudRate);
                    }
                }
            }
        }

        #endregion

        #region Movement Control Events

        private void aButtonExtend_MouseDown(object sender, MouseEventArgs e)
        {
            if (aTimerExtendButtonDown.Interval != this.ContinuousRotationCommandFrequency)
            {
                aTimerExtendButtonDown.Interval = this.ContinuousRotationCommandFrequency;
            }
            aTimerExtendButtonDown.Enabled = true;

            string speed = aTrackBarSpeed.Value.ToString();
            this.SendCommand(new Command(CommandTypeEnum.FINGER_ALL, CommandActionEnum.EXTEND, speed));
        }

        private void aTimerExtendButtonDown_Tick(object sender, EventArgs e)
        {
            string speed = aTrackBarSpeed.Value.ToString();
            this.SendCommand(new Command(CommandTypeEnum.FINGER_ALL, CommandActionEnum.EXTEND, speed));
        }

        private void aButtonExtend_MouseUp(object sender, MouseEventArgs e)
        {
            aTimerExtendButtonDown.Enabled = false;
        }

        private void aButtonContract_MouseDown(object sender, MouseEventArgs e)
        {
            if (aTimerContractButtonDown.Interval != this.ContinuousRotationCommandFrequency)
            {
                aTimerContractButtonDown.Interval = this.ContinuousRotationCommandFrequency;
            }
            aTimerContractButtonDown.Enabled = true;

            string speed = aTrackBarSpeed.Value.ToString();
            this.SendCommand(new Command(CommandTypeEnum.FINGER_ALL, CommandActionEnum.CONTRACT, speed));
        }

        private void aTimerContractButtonDown_Tick(object sender, EventArgs e)
        {
            string speed = aTrackBarSpeed.Value.ToString();
            this.SendCommand(new Command(CommandTypeEnum.FINGER_ALL, CommandActionEnum.CONTRACT, speed));
        }

        private void aButtonContract_MouseUp(object sender, MouseEventArgs e)
        {
            aTimerContractButtonDown.Enabled = false;
        }

        private void aButtonStop_Click(object sender, EventArgs e)
        {
            this.SendCommand(new Command(CommandTypeEnum.FINGER_ALL, CommandActionEnum.STOP));
        }

        private void aTrackBarSpeed_Scroll(object sender, EventArgs e)
        {
            aLabelSpeedValue.Text = aTrackBarSpeed.Value.ToString();
        }

        private void aButtonSetCommandTimer_Click(object sender, EventArgs e)
        {
            if (aTextboxSetCommandTimer.TextLength == 0)
            {
                aTextOutput.AppendText("Please type in value." + Environment.NewLine);
                return;
            }

            int result;
            if (Int32.TryParse(aTextboxSetCommandTimer.Text, out result))
            {
                if (result > 0)
                {
                    this.ContinuousRotationCommandFrequency = result;
                }
                this.SendCommand(new Command(CommandTypeEnum.ADMIN, CommandActionEnum.SET_MOVEMENT_COMMAND_TIMER, result.ToString()));
            }
            else
            {
                aTextOutput.AppendText("Please type in numeric value." + Environment.NewLine);
            }
        }

        private void aButtonSetCharBufferTimeout_Click(object sender, EventArgs e)
        {
            if (aTextboxSetCharBufferTimeout.TextLength == 0)
            {
                aTextOutput.AppendText("Please type in value." + Environment.NewLine);
                return;
            }

            int result;
            if (Int32.TryParse(aTextboxSetCharBufferTimeout.Text, out result))
            {
                this.SendCommand(new Command(CommandTypeEnum.ADMIN, CommandActionEnum.SET_CHAR_BUFFER_CLEAR_TIMER, result.ToString()));
            }
            else
            {
                aTextOutput.AppendText("Please type in numeric value." + Environment.NewLine);
            }
        }

        /// <summary>
        /// Encodes and sends provided command to microcontroller.
        /// </summary>
        /// <param name="command"></param>
        private void SendCommand(Command command)
        {
            string encodedCommand = this.CommandEncoder.EncodeCommand(command);
            string message = this.CommandTransmitter.Send(encodedCommand);
            aTextOutput.AppendText(message);
        }

        /// <summary>
        /// Sends EXTEND or CONTRACT command to microcontroller.
        /// </summary>
        private void SendRandomCommand()
        {
            Random rand = new Random();
            int command = rand.Next(1, 3);
            switch (command)
            {
                case 1:
                    this.SendCommand(new Command(CommandTypeEnum.FINGER_ALL, CommandActionEnum.EXTEND, "5"));
                    break;
                case 2:
                default:
                    this.SendCommand(new Command(CommandTypeEnum.FINGER_ALL, CommandActionEnum.CONTRACT, "5"));
                    break;
            }
        }

        #endregion

        #region Microcontroller Information

        private void aTimerMicrocontrollerOutput_Tick(object sender, EventArgs e)
        {
            string data = this.CommandTransmitter.Read();
            if (data != "")
            {
                aTextMicrocontroller.AppendText(data);
            }
        }

        #endregion

        // Slider to specify speed of contraction (1-3), button to contract, button to extend
        // Add threads to serial transmitter for reading and writing
        // Add selection menu for form to select type of communication
    }
}

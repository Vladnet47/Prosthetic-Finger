using System;
using System.IO;
using System.IO.Ports;
using System.Linq.Expressions;

namespace Transmission
{
    /// <summary>
    /// Used to communicate with microcontroller over serial wire
    /// </summary>
    class SerialTransmitter : ITransmitter
    {
        /// <summary>
        /// The port to which the microcontroller is connected.
        /// </summary>
        private SerialPort Port;

        /// <summary>
        /// List of available port names.
        /// </summary>
        /// <returns></returns>
        public string[] PortNames
        {
            get
            {
                try
                {
                    return SerialPort.GetPortNames();
                }
                catch (System.ComponentModel.Win32Exception e)
                {
                    return null;
                }
            }
        }

        /// <summary>
        /// List of available baud rates.
        /// </summary>
        public string[] BaudRates {
            get
            {
                return new string[6] { "9600", "19200", "38400", "57600", "74880", "115200" };
            }
        }

        /// <summary>
        /// Initializes read and write timeouts for transmitter.
        /// </summary>
        public SerialTransmitter(int writeTimeout = 500, int readTimeout = 500) {
            this.Port = new SerialPort
            {
                ReadTimeout = readTimeout,
                WriteTimeout = writeTimeout
            };
        }

        /// <summary>
        /// Opens port if not already opened.
        /// </summary>
        public string Connect(string portName, int baudRate)
        {
            if (this.Port.PortName != portName || this.Port.BaudRate != baudRate)
            {
                this.Disconnect();
                this.Port.PortName = portName;
                this.Port.BaudRate = baudRate;
            }

            if (!this.Port.IsOpen)
            {
                try
                {
                    this.Port.Open();
                    return "Opened port " + portName + "[" + baudRate + "]" + Environment.NewLine;
                }
                catch (Exception e) // IOException, UnauthorizedAccessException
                {
                    this.Disconnect();
                    return "Failed to open port " + portName + "[" + baudRate + "]:" + e.Message + Environment.NewLine;
                }
            }
            else
            {
                return "Port " + portName + "[" + baudRate + "] already open." + Environment.NewLine;
            }
        }

        public string Disconnect()
        {
            if (this.Port.IsOpen)
            {
                this.Port.Close();
                return "Closed port " + this.Port.PortName + "[" + this.Port.BaudRate + "]" + Environment.NewLine;
            }

            return "Failed to close: port not open" + Environment.NewLine;
        }

        /// <summary>
        /// Send string over serial.
        /// </summary>
        /// <param name="text"></param>
        public string Send(string text)
        {
            try
            {
                this.Port.Write(text);
                return "Successfully sent \"" + text + "\" to port " + this.Port.PortName + "[" + this.Port.BaudRate + "]" + Environment.NewLine;
            }
            catch (Exception e) // ArgumentNullException, TimeoutException
            {
                return "Failed to send \"" + text + "\": " + e.Message + Environment.NewLine;
            }
        }

        /// <summary>
        /// Read string from serial.
        /// </summary>
        /// <returns></returns>
        public String Read()
        {
            try
            {
                return this.Port.ReadExisting();
            }
            catch (Exception e) // InvalidOperationException, TimeoutException, IOException
            {
                return "Failed to read: " + e.Message + Environment.NewLine;
            }
        }
    }
}

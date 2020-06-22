using System;
using System.IO;
using System.IO.Ports;

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
        /// How many milliseconds to wait for write to finish.
        /// </summary>
        private readonly int WriteTimeout;

        /// <summary>
        /// How many milliseconds to wait for read to finish.
        /// </summary>
        private readonly int ReadTimeout;

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
                    Console.WriteLine("Unable to get list of available ports: " + e);
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
                return new string[4] { "9600", "19200", "38400", "57600" };
            }
        }

        /// <summary>
        /// Initializes read and write timeouts for transmitter.
        /// </summary>
        public SerialTransmitter(int writeTimeout = 500, int readTimeout = 500) {
            this.WriteTimeout = writeTimeout;
            this.ReadTimeout = readTimeout;
        }

        /// <summary>
        /// Send string over serial.
        /// </summary>
        /// <param name="text"></param>
        public bool Send(String text)
        {
            // Reopen port in case it closed and return false if failed.
            if (!this.IsPortOpen())
            {
                return false;
            }

            try
            {
                this.Port.Write(text);
                return true;
            }
            catch (InvalidOperationException e)
            {
                Console.WriteLine("Unable to read from serial because of port error: " + e.ToString());
                return false;
            }
            catch (ArgumentNullException e)
            {
                Console.WriteLine("Text to send is null: " + e.ToString());
                return false;
            }
            catch (TimeoutException e)
            {
                Console.WriteLine("Unable to read from serial because of timeout error: " + e.ToString());
                return false;
            }
        }

        /// <summary>
        /// Read string from serial.
        /// </summary>
        /// <returns></returns>
        public String Read()
        {
            // Reopen port in case it was closed, and return null if failed
            if (!this.IsPortOpen())
            {
                return null;
            }

            try
            {
                return this.Port.ReadLine();
            }
            catch (InvalidOperationException e)
            {
                Console.WriteLine("Unable to read from serial because of port error: " + e.ToString());
                return null;
            }
            catch (TimeoutException e)
            {
                Console.WriteLine("Unable to read from serial because of timeout error: " + e.ToString());
                return null; 
            }
        }

        /// <summary>
        /// Opens port if not already opened, and returns true if successful. Returns false otherwise.
        /// </summary>
        public bool OpenSerialPort(String portName, int baudRate)
        {
            // Don't do anything if correct port is already open
            if (this.IsPortOpen() && portName == this.Port.PortName && baudRate == this.Port.BaudRate)
            {
                return true;
            }

            // Close port if already opened
            this.CloseSerialPort();

            try
            {
                this.Port = new SerialPort()
                {
                    PortName = portName,
                    BaudRate = baudRate,
                    ReadTimeout = this.ReadTimeout,
                    WriteTimeout = this.WriteTimeout
                };

                return true;
            }
            catch (IOException e)
            {
                // If provided port name is unknown, or unable to open port
                Console.WriteLine("Unable to open serial port " + portName + " at baud rate " + baudRate + " with error: " + e);
                this.CloseSerialPort();
                return false;
            }
        }

        /// <summary>
        /// Closes port if it is open.
        /// </summary>
        public void CloseSerialPort()
        {
            if (this.Port != null)
            {
                this.Port.Close();
            }
        }

        /// <summary>
        /// Returns true if serial port is open, false otherwise
        /// </summary>
        /// <returns></returns>
        public bool IsPortOpen()
        {
            return this.Port != null && this.Port.IsOpen;
        }
    }
}

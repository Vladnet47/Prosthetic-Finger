using System;

namespace Transmission
{
    /// <summary>
    /// Interface for all types of data transmission (Serial, BLE, etc)
    /// </summary>
    interface ITransmitter
    {
        /// <summary>
        /// Send text to transmission target.
        /// </summary>
        /// <param name="text"></param>
        bool Send(String text);

        /// <summary>
        /// Read string from transmission target.
        /// </summary>
        /// <returns></returns>
        String Read();
    }
}

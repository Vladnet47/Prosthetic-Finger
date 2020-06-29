using System;
using System.Collections.Generic;

namespace Commands
{
    /// <summary>
    /// Used to encode commands into striing representation for transmission
    /// </summary>
    class Encoder
    {
        /// <summary>
        /// Character that the encoded command starts with,
        /// </summary>
        private readonly char StartChar;

        /// <summary>
        /// Character that the encoded command ends with.
        /// </summary>
        private readonly char EndChar;

        /// <summary>
        /// Conversions between CommandType enum and encoded strings
        /// </summary>
        private readonly IDictionary<CommandTypeEnum, String> TypeConversions;

        /// <summary>
        /// Conversions between CommandAction enum and encoded strings
        /// </summary>
        private readonly IDictionary<CommandActionEnum, String> ActionConversions;

        /// <summary>
        /// Initializes format-specific details to assist encoding, such as start/end characters and conversions between command enums and text.
        /// </summary>
        public Encoder()
        {
            this.StartChar = '#';
            this.EndChar = '\n';

            // Initialize conversions between command type enum value and characters sent to microcontroller.
            this.TypeConversions = new Dictionary<CommandTypeEnum, String>
            {
                [CommandTypeEnum.ADMIN] = "AD",
                [CommandTypeEnum.FINGER_ALL] = "FA"
            };

            // Initialize conversions between command action enum value and characters sent to microcontroller.
            this.ActionConversions = new Dictionary<CommandActionEnum, String>
            {
                [CommandActionEnum.SET_MOVEMENT_COMMAND_TIMER] = "TIMM",
                [CommandActionEnum.SET_CHAR_BUFFER_CLEAR_TIMER] = "TIMC",
                [CommandActionEnum.STOP] = "STOP",
                [CommandActionEnum.CONTRACT] = "CONT",
                [CommandActionEnum.EXTEND] = "EXTD",
            };
        }

        /// <summary>
        /// Returns encoded command string in the form '[STARTCHAR][TYPE][ACTION][DATA][ENDCHAR]' to be sent to microcontroller.
        /// </summary>
        /// <param name="command"></param>
        /// <returns></returns>
        public String EncodeCommand(Command command)
        {
            if (command.Type == CommandTypeEnum.UNDEFINED || command.Action == CommandActionEnum.UNDEFINED)
            {
                return null;
            }

            return this.StartChar + this.TypeConversions[command.Type] + this.ActionConversions[command.Action] + command.Data + this.EndChar;
        }
    }
}

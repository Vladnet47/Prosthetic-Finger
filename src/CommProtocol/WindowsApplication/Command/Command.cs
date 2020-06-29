using System;

namespace Commands
{
    /// <summary>
    /// Determines recipient of the command
    /// </summary>
    enum CommandTypeEnum {
        UNDEFINED,
        ADMIN,
        FINGER_ALL,
    }

    /// <summary>
    /// Determines what the command is instructed to do.
    /// </summary>
    enum CommandActionEnum {
        UNDEFINED,
        SET_MOVEMENT_COMMAND_TIMER,
        SET_CHAR_BUFFER_CLEAR_TIMER,
        STOP,
        CONTRACT,
        EXTEND
    }

    class Command
    {
        /// <summary>
        /// How the command is executed
        /// </summary>
        public readonly CommandTypeEnum Type;

        /// <summary>
        /// What the command eos when executed
        /// </summary>
        public readonly CommandActionEnum Action;

        /// <summary>
        /// Additional data passed with the command
        /// </summary>
        public readonly String Data;

        /// <summary>
        /// Initializes empty, undefined command
        /// </summary>
        public Command()
        {
            this.Type = CommandTypeEnum.UNDEFINED;
            this.Action = CommandActionEnum.UNDEFINED;
            this.Data = null;
        }

        /// <summary>
        /// Initializes command with provided data
        /// </summary>
        /// <param name="type"></param>
        /// <param name="action"></param>
        /// <param name="data"></param>
        public Command(CommandTypeEnum type, CommandActionEnum action, String data = "")
        {
            this.Type = type;
            this.Action = action;
            this.Data = data;
        }
    }
}

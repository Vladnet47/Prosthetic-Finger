#pragma once

// Type of command (what it is referring to)
enum class CommandTypeEnum {
	UNDEFINED,
	ADMIN,
	FINGER_ALL,
	Count
};

// Actions of commands
enum class CommandActionEnum {
	UNDEFINED,

	SET_MOVEMENT_COMMAND_TIMER,
	SET_CHAR_BUFFER_CLEAR_TIMER,

	STOP,
	CONTRACT,
	EXTEND,

	Count
};

const int DEFAULT_MOVEMENT_COMMAND_DURATION = 500;
const int DEFAULT_CHAR_BUFFER_CLEAR_DURATION = 5000;
const int COMMAND_START = '#';
const int COMMAND_END = '\n';
const int COMMAND_TYPE_LENGTH = 2;
const int COMMAND_ACTION_LENGTH = 4;
const int MAX_CHARACTERS_IN_BUFFER = 100;
const int MAX_COMMANDS_IN_BUFFER = 10;
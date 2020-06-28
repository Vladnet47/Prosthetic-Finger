#include "CommandConversions.h"

EnumMap<CommandTypeEnum>* COMMAND_TYPE_CONVERSIONS = new EnumMap<CommandTypeEnum>[(int)CommandTypeEnum::Count - 1]{
	   EnumMap<CommandTypeEnum>(new const char[COMMAND_TYPE_LENGTH] {'A', 'D'}, COMMAND_TYPE_LENGTH, CommandTypeEnum::ADMIN),
	   EnumMap<CommandTypeEnum>(new const char[COMMAND_TYPE_LENGTH] {'F', 'A'}, COMMAND_TYPE_LENGTH, CommandTypeEnum::FINGER_ALL)
};

EnumMap<CommandActionEnum>* COMMAND_ACTION_CONVERSIONS = new EnumMap<CommandActionEnum>[(int)CommandActionEnum::Count - 1]{
	EnumMap<CommandActionEnum>(new const char[COMMAND_ACTION_LENGTH] {'T', 'I', 'M', 'M'}, COMMAND_ACTION_LENGTH, CommandActionEnum::SET_MOVEMENT_COMMAND_TIMER),
	EnumMap<CommandActionEnum>(new const char[COMMAND_ACTION_LENGTH] {'T', 'I', 'M', 'C'}, COMMAND_ACTION_LENGTH, CommandActionEnum::SET_CHAR_BUFFER_CLEAR_TIMER),
	EnumMap<CommandActionEnum>(new const char[COMMAND_ACTION_LENGTH] {'C', 'O', 'N', 'T'}, COMMAND_ACTION_LENGTH, CommandActionEnum::CONTRACT),
	EnumMap<CommandActionEnum>(new const char[COMMAND_ACTION_LENGTH] {'E', 'X', 'T', 'D'}, COMMAND_ACTION_LENGTH, CommandActionEnum::EXTEND),
	EnumMap<CommandActionEnum>(new const char[COMMAND_ACTION_LENGTH] {'S', 'T', 'O', 'P'}, COMMAND_ACTION_LENGTH, CommandActionEnum::STOP)
};
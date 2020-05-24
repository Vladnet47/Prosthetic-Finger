#include "CommandConversions.h"

CommandConversions::CommandConversions() {
	this->actionConversions = new ActionConversion[NUM_ACTIONS]{
		ActionConversion(new const char[CommandConversions::COMMAND_ACTION_LENGTH] {'C', 'O', 'N', 'T'}, CommandAction::CONTRACT),
		ActionConversion(new const char[CommandConversions::COMMAND_ACTION_LENGTH] {'E', 'X', 'T', 'D'}, CommandAction::EXTEND),
		ActionConversion(new const char[CommandConversions::COMMAND_ACTION_LENGTH] {'S', 'T', 'O', 'P'}, CommandAction::STOP),
		ActionConversion(new const char[CommandConversions::COMMAND_ACTION_LENGTH] {'P', 'R', 'N', 'T'}, CommandAction::LIST_BUFFER)
	};

	this->typeConversions = new TypeConversion[NUM_TYPES]{
		TypeConversion(new const char[CommandConversions::COMMAND_TYPE_LENGTH] {'A', 'D'}, CommandType::ADMIN),
		TypeConversion(new const char[CommandConversions::COMMAND_TYPE_LENGTH] {'F', 'A'}, CommandType::FINGER_ALL),
		TypeConversion(new const char[CommandConversions::COMMAND_TYPE_LENGTH] {'F', 'I'}, CommandType::FINGER_INDEX),
		TypeConversion(new const char[CommandConversions::COMMAND_TYPE_LENGTH] {'F', 'M'}, CommandType::FINGER_MIDDLE),
		TypeConversion(new const char[CommandConversions::COMMAND_TYPE_LENGTH] {'F', 'R'}, CommandType::FINGER_RING),
		TypeConversion(new const char[CommandConversions::COMMAND_TYPE_LENGTH] {'F', 'L'}, CommandType::FINGER_LITTLE),
		TypeConversion(new const char[CommandConversions::COMMAND_TYPE_LENGTH] {'F', 'T'}, CommandType::FINGER_THUMB),
	};
}

CommandConversions::~CommandConversions() {
	delete[] this->typeConversions;
	delete[] this->actionConversions;
}

// Returns command type of array of characters, or undefined if unable to parse
const bool CommandConversions::tryParseAction(enum CommandAction& result, const char raw[], const int length) const {
	if (length != CommandConversions::COMMAND_ACTION_LENGTH) {
		return false;
	}

	for (int i = 0; i < NUM_ACTIONS; ++i) {
		// Get format
		const ActionConversion* actionConversion = &this->actionConversions[i];
		const char* format = actionConversion->raw;

		// Count number of matching characters
		int correctCount = 0;
		for (int j = 0; j < length; ++j) {
			if (raw[j] == format[j]) {
				++correctCount;
			}
		}

		// If all characters match conversion sequence, return its command type enum value
		if (correctCount == length) {
			result = actionConversion->val;
			return true;
		}
	}

	return false;
}

// Returns command type of array of characters, or undefined if unable to parse
const bool CommandConversions::tryParseType(enum CommandType& result, const char raw[], const int length) const {
	if (length != CommandConversions::COMMAND_TYPE_LENGTH) {
		return false;
	}

	for (int i = 0; i < NUM_TYPES; ++i) {
		// Get format
		const TypeConversion* typeConversion = &this->typeConversions[i];
		const char* format = typeConversion->raw;

		// Count number of matching characters
		int correctCount = 0;
		for (int j = 0; j < length; ++j) {
			if (raw[j] == format[j]) {
				++correctCount;
			}
		}

		// If all characters match conversion sequence, return its command type enum value
		if (correctCount == length) {
			result = typeConversion->val;
			return true;
		}
	}

	return false;
}
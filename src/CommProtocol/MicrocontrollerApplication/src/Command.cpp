#include "Command.h"

Command::Command() {
	this->commandType = CommandTypeEnum::UNDEFINED;
	this->commandAction = CommandActionEnum::UNDEFINED;
	this->numericData = 0;
}

Command::Command(enum CommandTypeEnum CommandTypeEnum, enum CommandActionEnum CommandActionEnum, int numericData) {
	this->commandType = CommandTypeEnum;
	this->commandAction = CommandActionEnum;
	this->numericData = numericData;
}

Command::Command(const Command& other) {
	*this = other;
}

Command::~Command() {}

// Converts the provided character array into command and returns true if successful, false otherwise (leaves command in undefined state)
const bool Command::tryParse(const char* chars, const int length) {
	// Make sure provided character array is in command format
	if (chars == nullptr || length < 2 + COMMAND_TYPE_LENGTH + COMMAND_ACTION_LENGTH || chars[0] != COMMAND_START || chars[length - 1] != COMMAND_END) {
		return false;
	}

	// Parse type
	int start = 1;
	int end = 1 + COMMAND_TYPE_LENGTH;
	enum CommandTypeEnum parsedType;
	if (this->tryParseEnum(parsedType, chars, length, start, end, COMMAND_TYPE_CONVERSIONS, (int)CommandTypeEnum::Count - 1)) {
		this->commandType = parsedType;
	}
	else {
		return false;
	}

	// Parse action
	start = end;
	end = end + COMMAND_ACTION_LENGTH;
	enum CommandActionEnum parsedAction;
	if (this->tryParseEnum(parsedAction, chars, length, start, end, COMMAND_ACTION_CONVERSIONS, (int)CommandActionEnum::Count - 1)) {
		this->commandAction = parsedAction;
	}
	else {
		return false;
	}

	// Parse data, if available
	start = end;
	end = length - 1;
	int parsedData = 0;
	if (end - start == 0 || this->tryParseInteger(parsedData, chars, length, start, end)) {
		this->numericData = parsedData;
	}
	else {
		return false;
	}

	return true;
}

// Returns true if successfully parsed integer from the character buffer and sets result equal to that integer.
// Otherwise, returns false and leaves result integer in undefined state
const bool Command::tryParseInteger(int& result, const char chars[], const int length, const int start, const int end) const {
	// Return false if empty
	if (chars == nullptr || length == 0 || start < 0 || end > length) {
		return false;
	}

	// Inspect every character in array from the back
	result = 0;
	for (int i = end - 1; i >= start; --i) {
		if (chars[i] == '-' && i == start) { // If '-' character, it must be the first in the list
			result *= -1;
		}
		else if (chars[i] - '0' <= 9) { // If numeric, convert to integer
			result += (chars[i] - '0') * this->exponent(10, end - i - 1);
		}
		else { // Character not numeric, or '-' character in wrong place
			return false;
		}
	}

	return true;
}

// Returns base to the power of exponent (1 if exp <= 0)
const int Command::exponent(const int base, const int exp) const {
	int result = 1;
	for (int i = 0; i < exp; ++i) {
		result *= base;
	}
	return result;
}

// Returns command type
const enum CommandTypeEnum Command::type() const {
	return this->commandType;
}

// Returns command action
const enum CommandActionEnum Command::action() const {
	return this->commandAction;
}

// Returns numerical command data
const int Command::data() const {
	return this->numericData;
}

// Sets object data equal to other
Command& Command::operator=(const Command& other) {
	if (this != &other) {
		this->commandType = other.type();
		this->commandAction = other.action();
		this->numericData = other.data();
	}

	return *this;
}

// Returns true if all object data is the same, false otherwise
const bool Command::operator==(const Command& other) const {
	return this->type() == other.type() && this->action() == other.action() && this->data() == other.data();
}

// Returns true if object data does not match, false otherwise
const bool Command::operator!=(const Command& other) const {
	return !(*this == other);
}

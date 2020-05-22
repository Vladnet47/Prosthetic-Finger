#include "CommandInterpreter.h"

// Conversions used to determine type of command from character array
CommandTypeMap* CommandInterpreter::conversions = new CommandTypeMap[NUMBER_OF_COMMANDS]{
	CommandTypeMap(new char[CommandInterpreter::COMMAND_LENGTH] {'C', 'O', 'N', 'T'}, CONTRACT_HAND),
	CommandTypeMap(new char[CommandInterpreter::COMMAND_LENGTH] {'E', 'X', 'T', 'D'}, EXTEND_HAND),
	CommandTypeMap(new char[CommandInterpreter::COMMAND_LENGTH] {'S', 'T', 'O', 'P'}, STOP),
	CommandTypeMap(new char[CommandInterpreter::COMMAND_LENGTH] {'P', 'R', 'N', 'T'}, LIST_BUFFER)
};

CommandInterpreter::CommandInterpreter() {}
CommandInterpreter::~CommandInterpreter() {}

// Returns true if successfully parsed command type from provided array of characters and sets 'type' parameter
// to command type enum value. Returns false if failed to parse command from chars.
bool CommandInterpreter::tryParseType(enum CommandType& type, const char chars[], const int length) {
	if (chars == nullptr || length != CommandInterpreter::COMMAND_LENGTH) {
		return false;
	}

	for (int i = 0; i < NUMBER_OF_COMMANDS; ++i) {
		// Get required format
		const char* format = CommandInterpreter::conversions->raw();

		// Count number of matching characters
		int correctCount = 0;
		for (int j = 0; j < COMMAND_LENGTH; ++j) {
			if (chars[j] == format[j]) {
				++correctCount;
			}
		}

		// If all are matching, set 'type' to correct enum value
		if (correctCount == COMMAND_LENGTH) {
			type = CommandInterpreter::conversions->val();
			return true;
		}
	}

	return false;
}

// Returns true if successfully parsed integer from provided character array and sets
// result equal to the value. If unable to parse integer, returns false, and leaves result in
// undefined state.
bool CommandInterpreter::tryParseInt(int& result, const char chars[], const int length) {
	if (chars == nullptr) {
		return false;
	}

	result = 0;

	// Inspect every character in array from the back
	for (int i = length - 1; i >= 0; --i) {
		char c = chars[i];

		// If '-' character, it must be the first in the list
		if (c == '-' && i == 0) {
			result *= -1;
		}
		// If numeric, convert to integer
		else if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') {
			result += (c - '0') * CommandInterpreter::pow(10, length - i - 1);
		}
		// Character not numeric, or '-' character in wrong place
		else {
			return false;
		}
	}

	return true;
}

// Returns base raised to the power of exponent
int CommandInterpreter::pow(const int base, const int exponent) {
	if (exponent <= 0) {
		return 1;
	}

	int result = base;
	for (int i = 1; i < exponent; ++i) {
		result *= result;
	}
	return result;
}

// Returns subset of provided array from start (inclusive) to end (exclusive), or nullptr if failed
char* CommandInterpreter::arraySubset(const char chars[], const int length, const int start, const int end) {
	// Check if valid indeces/lengths
	const int subsetLength = end - start;
	if (length <= 0 && subsetLength < length) {
		return nullptr;
	}

	char* result = new char[subsetLength];

	// Copy array subset into result
	for (int i = 0; i < subsetLength; ++i) {
		result[i] = chars[start + i];
	}

	return result;
}

// Parses command(s) from provided cstring buffer. Sets 'commands' parameter to array of command objects, and returns
// size of said array. 
// - If a command cannot be identified, it's type is set as UNDEFINED and the respective chars are stored in its blob data.
// - If the command data is a valid integer, it is stored as numeric data. Otherwise, the command data is stored in blob data.
int CommandInterpreter::parseCommands(Command*& commands, const char chars[], const int length) {
	if (chars == nullptr || length <= 0) {
		return 0;
	}

	// Count number of commands in list (basically, search for matches of "# ... \n")
	int count = 0, start = 0, end = 0;
	while (start < length && end < length) {
		if (chars[start] != CommandInterpreter::COMMAND_START) {
			++start;
		}
		else if (chars[end] == CommandInterpreter::COMMAND_END) {
			++count;
			start = end + 1;
		}
		++end;
	}

	if (count == 0) {
		return 0;
	}

	// Create array for all commands (which are set to undefined if invalid)
	commands = new Command[count];

	// Go through characters and convert to command objects
	int index = 0;
	start = 0, end = 0;
	while (index < count && end < length) {
		// If start symbol doesn't indicate the start of a command, increment both start and end
		if (chars[start] != CommandInterpreter::COMMAND_START) {
			++start;
		}
		// If end symbol is found, the symbols between the start and end are converted into a command object
		else if (chars[end] == CommandInterpreter::COMMAND_END) {
			const int commandLength = end - start - 1;

			// Ensure valid number of symbols for a command
			if (commandLength < CommandInterpreter::COMMAND_LENGTH) {
				commands[index] = Command(UNDEFINED, 0, arraySubset(chars, length, start + 1, end), commandLength);
				++index;
				start = end;
				++end;
				continue;
			}

			const int dataLength = commandLength - CommandInterpreter::COMMAND_LENGTH;

			// Copy symbols that represent the command type
			char* typeChars = arraySubset(chars, length, start + 1, start + 1 + COMMAND_LENGTH);

			// Parse command type
			enum CommandType type;
			bool successfullyParsed = CommandInterpreter::tryParseType(type, typeChars, COMMAND_LENGTH);
			delete[] typeChars;

			// If failed to parse, create undefined command and put buffer contents into its blob data
			if (!successfullyParsed) {
				commands[index] = Command(UNDEFINED, 0, arraySubset(chars, length, start + 1, end), commandLength);
				++index;
				start = end;
				++end;
				continue;
			}

			// Copy the symbols that represent the command data
			char* dataChars = arraySubset(chars, length, start + 1 + COMMAND_LENGTH, end);

			// Parse int from data
			int nData;
			successfullyParsed = CommandInterpreter::tryParseInt(nData, dataChars, dataLength);

			// If successfully parsed, store as int. If unable to parse, store symbols as blob data instead.
			if (successfullyParsed) {
				delete[] dataChars;
				commands[index] = Command(type, nData);
			}
			else {
				commands[index] = Command(type, 0, dataChars, dataLength);
			}

			++index;
			start = end;
		}

		++end;
	}

	return count;
}



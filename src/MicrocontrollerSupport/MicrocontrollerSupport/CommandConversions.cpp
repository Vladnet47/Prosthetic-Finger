#include "CommandConversions.h"

CommandConversions::CommandConversions() {
	this->conversions = new Conversion[CommandConversions::NUM_CONVERSIONS]{
		Conversion(new const char[CommandConversions::COMMAND_LENGTH] {'C', 'O', 'N', 'T'}, CONTRACT_HAND),
		Conversion(new const char[CommandConversions::COMMAND_LENGTH] {'E', 'X', 'T', 'D'}, EXTEND_HAND),
		Conversion(new const char[CommandConversions::COMMAND_LENGTH] {'S', 'T', 'O', 'P'}, STOP),
		Conversion(new const char[CommandConversions::COMMAND_LENGTH] {'P', 'R', 'N', 'T'}, LIST_BUFFER)
	};
}

CommandConversions::~CommandConversions() {
	delete[] this->conversions;
}

// Returns command type of array of characters, or undefined if unable to parse
const enum CommandType CommandConversions::tryParse(const char raw[], const int length) const {
	for (int i = 0; i < CommandConversions::NUM_CONVERSIONS; ++i) {
		// Get format
		const Conversion* conversion = &this->conversions[i];
		const char* format = conversion->raw;

		// Count number of matching characters
		int correctCount = 0;
		for (int j = 0; j < CommandConversions::COMMAND_LENGTH; ++j) {
			if (raw[j] == format[j]) {
				++correctCount;
			}
		}

		// If all characters match conversion sequence, return its command type enum value
		if (correctCount == CommandConversions::COMMAND_LENGTH) {
			return conversion->val;
		}
	}

	return UNDEFINED;
}
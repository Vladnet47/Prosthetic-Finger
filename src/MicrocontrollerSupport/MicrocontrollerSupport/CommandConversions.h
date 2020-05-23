#pragma once
#include "Command.h"

class CommandConversions {
public:
	static const int COMMAND_START = '#';
	static const int COMMAND_END = '\n';
	static const int COMMAND_LENGTH = 4;
	static const int NUM_CONVERSIONS = 4;

	CommandConversions();
	~CommandConversions();

	const enum CommandType tryParse(const char raw[], const int length) const;

private:
	// Struct used to map between raw command characters and their command type enum value
	struct Conversion {
		const char* raw;
		enum CommandType val;

		Conversion(const char raw[], const enum CommandType val) {
			this->raw = raw;
			this->val = val;
		}

		~Conversion() {
			delete[] this->raw;
		}
	};

	const Conversion* conversions;
};
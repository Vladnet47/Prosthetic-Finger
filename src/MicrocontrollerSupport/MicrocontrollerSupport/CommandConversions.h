#pragma once
#include "Command.h"

class CommandConversions {
public:
	static const int COMMAND_START = '#';
	static const int COMMAND_END = '\n';
	static const int COMMAND_TYPE_LENGTH = 2;
	static const int COMMAND_ACTION_LENGTH = 4;

	CommandConversions();
	~CommandConversions();

	const bool tryParseAction(enum CommandAction& result, const char raw[], const int length) const;
	const bool tryParseType(enum CommandType& result, const char raw[], const int length) const;

private:
	// Struct used to map between raw command characters and their command type enum value
	struct TypeConversion {
		const char* raw;
		enum CommandType val;

		TypeConversion(const char raw[], const enum CommandType action) {
			this->raw = raw;
			this->val = action;
		}

		~TypeConversion() {
			delete[] this->raw;
		}
	};

	// Struct used to map between raw command characters and their command action enum value
	struct ActionConversion {
		const char* raw;
		enum CommandAction val;

		ActionConversion(const char raw[], const enum CommandAction action) {
			this->raw = raw;
			this->val = action;
		}

		~ActionConversion() {
			delete[] this->raw;
		}
	};
	
	const TypeConversion* typeConversions;
	const ActionConversion* actionConversions;
};
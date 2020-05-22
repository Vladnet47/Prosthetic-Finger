#pragma once
#include "Command.h"

// Mapping between raw user format ("CONT", "PRNT", etc...) and correct command type enum value.
struct CommandTypeMap {
	const char* raw;
	enum CommandType val;

	CommandTypeMap(const char raw[], const enum CommandType val) {
		this->raw = raw;
		this->val = val;
	}

	~CommandTypeMap() {
		delete[] this->raw;
	}
};

class CommandInterpreter {
	public:
		static const int NUM_CONVERSIONS = 4;	// Number of conversion patterns defined in constructor
		static const int COMMAND_LENGTH = 4;	// Length of command ("CONT", "PRNT", etc), excludes length of data
		static const int COMMAND_START = '#';	// Character the command starts with
		static const int COMMAND_END = '\n';	// Character the command ends with

		CommandInterpreter();
		~CommandInterpreter();

		int parseCommands(Command*& commands, const char chars[], const int length) const;
	private:
		// Used to categorize commands sent to the microcontroller by the user. Defined in cpp
		CommandTypeMap* conversions;

		bool tryParseType(enum CommandType& type, const char chars[], const int length) const;
		bool tryParseInt(int& result, const char chars[], const int length) const;
		int pow(const int base, const int exponent) const;
		char* arraySubset(const char chars[], const int length, const int start, const int end) const;
};
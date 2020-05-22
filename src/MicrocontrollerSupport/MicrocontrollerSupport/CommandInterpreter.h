#pragma once
#include "Command.h"

struct CommandTypeMap {
public:
	CommandTypeMap(const char* raw, const enum CommandType val) {
		this->rawFormat = raw;
		this->convertedValue = val;
	}
	~CommandTypeMap() {
		delete[] this->rawFormat;
	}
	const char* raw() {
		return this->rawFormat;
	}
	const enum CommandType val() {
		return this->convertedValue;
	}
private:
	const char* rawFormat;
	enum CommandType convertedValue;
};

class CommandInterpreter {
	public:
		static const int COMMAND_LENGTH = 4;
		static const int COMMAND_START = '#';
		static const int COMMAND_END = '\n';

		// Used to categorize commands sent to the microcontroller by the user. Defined in cpp
		static CommandTypeMap* conversions;

		CommandInterpreter();
		~CommandInterpreter();

		static bool tryParseType(enum CommandType& type, const char chars[], const int length);
		static bool tryParseInt(int& result, const char chars[], const int length);
		static int pow(const int base, const int exponent);
		static char* arraySubset(const char chars[], const int length, const int start, const int end);
		static int parseCommands(Command*& commands, const char chars[], const int length);
	private:		
};
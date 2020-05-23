#pragma once
#include "Command.h"
#include "ElasticBuffer.h"

// Decodes commands from character stream sent to the microcontroller
class CommandDecoder {
public:
	static const int COMMAND_START = '#';
	static const int COMMAND_END = '\n';
	static const int COMMAND_LENGTH = 4;
	static const int NUM_CONVERSIONS = 4;

	CommandDecoder();
	~CommandDecoder();
	const void addChar(const char nextChar);
	const void addChars(const char* nextChars, const int length);
	const bool hasNext() const;
	const Command* next();
	const void clear();
private:
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

	const CommandTypeMap* conversions;
	ElasticBuffer<Command>* commandBuffer;
	ElasticBuffer<char>* charBuffer;
	bool encounteredStart;

	const bool tryParseType(enum CommandType& type) const;
	const bool tryParseInt(int& result)const;
	const char* dumpCharBuffer();
	const int pow(const int base, const int exponent) const;
};
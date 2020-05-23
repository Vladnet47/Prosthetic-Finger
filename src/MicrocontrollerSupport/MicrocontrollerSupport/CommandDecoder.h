#pragma once
#include "Command.h"
#include "CommandConversions.h"
#include "ElasticBuffer.h"

// Decodes commands from stream of characters sent to the microcontroller. Buffers incoming characters
// to prevent data loss from signal delays.
class CommandDecoder {
public:
	CommandDecoder();
	~CommandDecoder();
	const void addChar(const char nextChar);
	const void addChars(const char* nextChars, const int length);
	const bool hasNext() const;
	const Command* next();
	const void clear();
private:
	CommandConversions* conversions;
	ElasticBuffer<Command>* commandBuffer;	// Buffer for output parsed commands
	ElasticBuffer<char>* charBuffer;		// Buffer for input characters
	bool encounteredStart;					// Helpful indicator for determining whether or not to parse the characters into a command

	const bool tryParseType(enum CommandType& type) const;
	const bool tryParseInt(int& result)const;
	const char* dumpCharBuffer();
	const int pow(const int base, const int exponent) const;
};
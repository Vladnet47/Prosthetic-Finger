#pragma once
#include "Util.h"
#include "Timer.h"
#include "EnumMap.h"
#include "Command.h"
#include "ElasticBuffer.h"

// Decodes commands from stream of characters sent to the microcontroller. Buffers incoming characters
// to prevent data loss from signal delays.
class CommandDecoder {
public:
	static const int COMMAND_START = '#';
	static const int COMMAND_END = '\n';
	static const int COMMAND_TYPE_LENGTH = 2;
	static const int COMMAND_ACTION_LENGTH = 4;
	static const int NUM_TYPE_CONVERSIONS = 7;
	static const int NUM_ACTION_CONVERSIONS = 4;

	CommandDecoder();
	~CommandDecoder();

	const void addChar(const char nextChar);
	const void addChars(const char* nextChars, const int length);
	const bool hasNext() const;
	const Command* next();
	const void clear();
private:
	// Conversions between character stream and command enum values
	EnumMap<CommandType>* typeConversions;
	EnumMap<CommandAction>* actionConversions;

	Buffer<Command>* commandBuffer;			// Buffer for output parsed commands
	Buffer<char>* charBuffer;				// Buffer for input characters
	bool encounteredStart;					// Helpful indicator for determining whether or not to parse the characters into a command

	template <class T>
	const bool tryParse(T& result, const EnumMap<T>* conversions, const int numConversions) const;
	const int copyCharBuffer(char*& result, const int numberOfChars) const;
	const int dumpAndCopyCharBuffer(char*& result, const int numberOfChars);
	void dumpCharBuffer(const int numberOfChars);
};

template <class T>
// Tries to parse enum value from the next bytes in buffer. Returns true and sets result to parsed value if successful, returns false and leaves
// result in undefined state otherwise
const bool CommandDecoder::tryParse(T& result, const EnumMap<T>* conversions, const int numConversions) const {
	if (conversions == nullptr || numConversions == 0 || this->charBuffer->size() < conversions[0].length()) {
		return false;
	}

	const int conversionLength = conversions[0].length();

	// Copy required amount of characters from the buffer
	char* bytes = nullptr;
	int numberOfBytes = this->copyCharBuffer(bytes, conversionLength);

	// Buffer contains less characters than required
	if (numberOfBytes != conversionLength) {
		return false;
	}

	for (int i = 0; i < numConversions; ++i) {
		// Only return true if successfully parsed enum value from characters
		if (conversions[i].tryParse(result, bytes, numberOfBytes)) {
			delete[] bytes;
			return true;
		}
	}

	delete[] bytes;
	return false;
}
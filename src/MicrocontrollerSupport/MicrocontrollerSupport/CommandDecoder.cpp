#include "CommandDecoder.h"

CommandDecoder::CommandDecoder() {
	this->conversions = new CommandConversions();

	// Initialize character and command length buffers
	this->commandBuffer = new ElasticBuffer<Command>();
	this->charBuffer = new ElasticBuffer<char>();
	this->encounteredStart = false;
}

CommandDecoder::~CommandDecoder() {
	delete this->conversions;
	delete this->commandBuffer;
	delete this->charBuffer;
}

// Adds single character to character buffer, to be decoded into a command
const void CommandDecoder::addChar(const char nextChar) {
	const int size = this->charBuffer->size();

	if (this->encounteredStart && nextChar == CommandConversions::COMMAND_START || !this->encounteredStart && nextChar == CommandConversions::COMMAND_END) {
		// Illegal sequence of characters (two start symbols without end in between, end symbol without start)
		// Create new command and add it to command buffer
		this->commandBuffer->push(Command(UNDEFINED, 0, this->dumpCharBuffer(), size));
	}
	else if (nextChar == CommandConversions::COMMAND_START) {
		// Have not yet encountered start symbol, so set that to true
		this->encounteredStart = true;
	}
	else if (nextChar == CommandConversions::COMMAND_END) {
		// Parse command from character buffer and add to buffer
		this->encounteredStart = false;

		// Try to parse command from characters in buffer
		enum CommandType commandType;
		if (this->tryParseType(commandType)) {
			// On success, remove command characters from buffer
			for (int i = 0; i < CommandConversions::COMMAND_LENGTH; ++i) {
				delete this->charBuffer->pop();
			}

			// Try to parse integer from remaining characters in buffer
			int numericData;
			if (this->tryParseInt(numericData)) {
				// On success, store integer with command
				this->commandBuffer->push(Command(commandType, numericData));
				this->charBuffer->clear();
			}
			else {
				// On failure, store characters in command blob data
				this->commandBuffer->push(Command(commandType, 0, this->dumpCharBuffer(), size - CommandConversions::COMMAND_LENGTH));
			}
		}
		else {
			// On failure, store command contents in blob data of new undefined command
			this->commandBuffer->push(Command(UNDEFINED, 0, this->dumpCharBuffer(), size));
		}
	}
	else {
		// If insignificant character, simply add it to buffer
		this->charBuffer->push(nextChar);
	}
}

// Adds array of characters to the character buffer, to be decoded into commands
const void CommandDecoder::addChars(const char* nextChars, const int length) {
	if (nextChars != nullptr) {
		for (int i = 0; i < length; ++i) {
			this->addChar(nextChars[i]);
		}
	}
}

// Returns true if at least one command has been parsed
const bool CommandDecoder::hasNext() const {
	return !this->commandBuffer->isEmpty();
}

// Returns oldest parsed command
const Command* CommandDecoder::next() {
	return this->commandBuffer->pop();
}

// Clears all buffers
const void CommandDecoder::clear() {
	this->commandBuffer->clear();
	this->charBuffer->clear();
	this->encounteredStart = false;
}

// Returns true if successfully parsed command type from provided array of characters and sets 'type' parameter
// to command type enum value. Returns false if failed to parse command from chars.
const bool CommandDecoder::tryParseType(enum CommandType& type) const {
	const int size = this->charBuffer->size();
	if (size < CommandConversions::COMMAND_LENGTH) {
		return false;
	}

	// Copy first COMMAND_LENGTH characters of char buffer
	char* chars = new char[CommandConversions::COMMAND_LENGTH];
	for (int i = 0; i < CommandConversions::COMMAND_LENGTH; ++i) {
		if (i >= size) {
			chars[i] = '-';
		}
		else {
			chars[i] = *this->charBuffer->get(i);
		}
	}

	type = this->conversions->tryParse(chars, CommandConversions::COMMAND_LENGTH);
	delete chars;
	return type != UNDEFINED;
}

// Returns true if successfully parsed integer from the character buffer
const bool CommandDecoder::tryParseInt(int& result) const {
	result = 0;

	const int size = this->charBuffer->size();

	// Inspect every character in array from the back
	for (int i = size - 1; i >= 0; --i) {
		// Get reference to character
		const char* c = this->charBuffer->get(i);

		// If '-' character, it must be the first in the list
		if (*c == '-' && i == 0) {
			result *= -1;
		}
		// If numeric, convert to integer
		else if (*c == '0' || *c == '1' || *c == '2' || *c == '3' || *c == '4' || *c == '5' || *c == '6' || *c == '7' || *c == '8' || *c == '9') {
			result += (*c - '0') * Util::Math::pow(10, size - i - 1);
		}
		// Character not numeric, or '-' character in wrong place
		else {
			return false;
		}
	}

	return true;
}

// Adds undefined command to buffer and dumps contents of char buffer into it's blob storage
const char* CommandDecoder::dumpCharBuffer() {
	const int size = this->charBuffer->size();

	// Copy buffer contents into a byte array
	char* blob = new char[size];
	for (int i = 0; i < size; ++i) {
		const char* currentChar = this->charBuffer->pop();
		blob[i] = *currentChar;
		delete currentChar;
	}

	return blob;
}
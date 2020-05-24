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
	int bufferSize = this->charBuffer->size();

	if (this->encounteredStart && nextChar == CommandConversions::COMMAND_START || !this->encounteredStart && nextChar == CommandConversions::COMMAND_END) {
		// Illegal sequence of characters (two start symbols without end in between, end symbol without start)
		// Create new command and add it to command buffer
		this->commandBuffer->push(Command(CommandType::UNDEFINED, CommandAction::UNDEFINED, 0, this->dumpCharBuffer(), bufferSize));
	}
	else if (nextChar == CommandConversions::COMMAND_START) {
		// Have not yet encountered start symbol, so set that to true
		this->encounteredStart = true;
	}
	else if (nextChar == CommandConversions::COMMAND_END) {
		this->encounteredStart = false;

		// Try to parse the command type
		enum CommandType commandType;
		char* bytes = nullptr;
		int numberOfBytes = this->copyCharBuffer(bytes, CommandConversions::COMMAND_TYPE_LENGTH);
		bool parsed = this->conversions->tryParseType(commandType, bytes, numberOfBytes);
		delete[] bytes;

		// If unsuccessfull, store remaining bytes in buffer as blob
		if (!parsed) {
			this->commandBuffer->push(Command(CommandType::UNDEFINED, CommandAction::UNDEFINED, 0, this->dumpCharBuffer(), bufferSize));
			return;
		}

		// If successfull, remove type chars from the buffer
		for (int i = 0; i < CommandConversions::COMMAND_TYPE_LENGTH; ++i) {
			delete this->charBuffer->pop();
		}
		bufferSize -= CommandConversions::COMMAND_TYPE_LENGTH;

		// Try to parse the command action
		enum CommandAction commandAction;
		bytes = nullptr;
		numberOfBytes = this->copyCharBuffer(bytes, CommandConversions::COMMAND_ACTION_LENGTH);
		parsed = this->conversions->tryParseAction(commandAction, bytes, numberOfBytes);
		delete[] bytes;

		if (!parsed) {
			// If unsuccessfull, store remaining bytes in buffer as blob
			this->commandBuffer->push(Command(commandType, CommandAction::UNDEFINED, 0, this->dumpCharBuffer(), bufferSize));
			return;
		}

		// If successfull, remove action chars from the buffer
		for (int i = 0; i < CommandConversions::COMMAND_ACTION_LENGTH; ++i) {
			delete this->charBuffer->pop();
		}
		bufferSize -= CommandConversions::COMMAND_ACTION_LENGTH;

		
		// Try to parse and integer from the data
		int numericData;
		bytes = nullptr;
		numberOfBytes = this->copyCharBuffer(bytes, bufferSize);
		parsed = Util::Math::tryParseInt(numericData, bytes, numberOfBytes);
		delete[] bytes;

		if (!parsed) {
			// If unsuccessful, store data chars as blob data
			this->commandBuffer->push(Command(commandType, commandAction, 0, this->dumpCharBuffer(), bufferSize));
		}
		else {
			// If successfull, store integer and remove bytes from buffer
			this->commandBuffer->push(Command(commandType, commandAction, numericData));
			this->charBuffer->clear();
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

// Returns array of the first 'length' characters from char buffer
const int CommandDecoder::copyCharBuffer(char*& result, const int length) const {
	if (length <= 0) {
		return 0;
	}

	int maxLength = Util::Math::min(length, this->charBuffer->size());

	// Copy buffer contents into a byte array
	result = new char[maxLength];
	for (int i = 0; i < maxLength; ++i) {
		result[i] = *this->charBuffer->get(i);
	}

	return maxLength;
}

// Returns array of the first 'length' characters from char buffer
const char* CommandDecoder::dumpCharBuffer() const {
	char* result;
	this->copyCharBuffer(result, this->charBuffer->size());
	this->charBuffer->clear();
	return result;
}
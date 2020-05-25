#include "CommandDecoder.h"

CommandDecoder::CommandDecoder() {
	// Define formats for command type conversion
	this->typeConversions = new EnumMap<CommandType>[CommandDecoder::NUM_TYPE_CONVERSIONS] {
		EnumMap<CommandType>(new const char[CommandDecoder::COMMAND_TYPE_LENGTH] {'A', 'D'}, CommandDecoder::COMMAND_TYPE_LENGTH, CommandType::ADMIN),
		EnumMap<CommandType>(new const char[CommandDecoder::COMMAND_TYPE_LENGTH] {'F', 'A'}, CommandDecoder::COMMAND_TYPE_LENGTH, CommandType::FINGER_ALL),
		EnumMap<CommandType>(new const char[CommandDecoder::COMMAND_TYPE_LENGTH] {'F', 'I'}, CommandDecoder::COMMAND_TYPE_LENGTH, CommandType::FINGER_INDEX),
		EnumMap<CommandType>(new const char[CommandDecoder::COMMAND_TYPE_LENGTH] {'F', 'M'}, CommandDecoder::COMMAND_TYPE_LENGTH, CommandType::FINGER_MIDDLE),
		EnumMap<CommandType>(new const char[CommandDecoder::COMMAND_TYPE_LENGTH] {'F', 'R'}, CommandDecoder::COMMAND_TYPE_LENGTH, CommandType::FINGER_RING),
		EnumMap<CommandType>(new const char[CommandDecoder::COMMAND_TYPE_LENGTH] {'F', 'L'}, CommandDecoder::COMMAND_TYPE_LENGTH, CommandType::FINGER_LITTLE),
		EnumMap<CommandType>(new const char[CommandDecoder::COMMAND_TYPE_LENGTH] {'F', 'T'}, CommandDecoder::COMMAND_TYPE_LENGTH, CommandType::FINGER_THUMB),
	};

	// Define formats for command action conversion
	this->actionConversions = new EnumMap<CommandAction>[CommandDecoder::NUM_ACTION_CONVERSIONS]{
		EnumMap<CommandAction>(new const char[CommandDecoder::COMMAND_ACTION_LENGTH] {'C', 'O', 'N', 'T'}, CommandDecoder::COMMAND_ACTION_LENGTH, CommandAction::CONTRACT),
		EnumMap<CommandAction>(new const char[CommandDecoder::COMMAND_ACTION_LENGTH] {'E', 'X', 'T', 'D'}, CommandDecoder::COMMAND_ACTION_LENGTH, CommandAction::EXTEND),
		EnumMap<CommandAction>(new const char[CommandDecoder::COMMAND_ACTION_LENGTH] {'S', 'T', 'O', 'P'}, CommandDecoder::COMMAND_ACTION_LENGTH, CommandAction::STOP),
		EnumMap<CommandAction>(new const char[CommandDecoder::COMMAND_ACTION_LENGTH] {'P', 'R', 'N', 'T'}, CommandDecoder::COMMAND_ACTION_LENGTH, CommandAction::LIST_BUFFER)
	};

	// Initialize character and command buffers
	this->commandBuffer = new ElasticBuffer<Command>(); 
	this->charBuffer = new ElasticBuffer<char>();
	this->encounteredStart = false;
}

CommandDecoder::~CommandDecoder() {
	delete[] this->typeConversions;
	delete[] this->actionConversions;
	delete this->commandBuffer;
	delete this->charBuffer;
}

// Adds single character to character buffer, to be decoded into a command
const void CommandDecoder::addChar(const char nextChar) {
	int bufferSize = this->charBuffer->size();
	char* bytes = nullptr;
	int numberOfBytes;

	if (this->encounteredStart && nextChar == CommandDecoder::COMMAND_START || !this->encounteredStart && nextChar == CommandDecoder::COMMAND_END) {
		// Illegal sequence of characters (two start symbols without end in between, end symbol without start)
		// Create new command and add it to command buffer
		numberOfBytes = this->dumpAndCopyCharBuffer(bytes, bufferSize);
		this->commandBuffer->push(Command(CommandType::UNDEFINED, CommandAction::UNDEFINED, 0, bytes, numberOfBytes));
	}
	else if (nextChar == CommandDecoder::COMMAND_START) {
		// Have not yet encountered start symbol, so set that to true
		this->encounteredStart = true;
	}
	else if (nextChar == CommandDecoder::COMMAND_END) {
		this->encounteredStart = false;

		// Try to parse the command type
		enum CommandType commandType;
		bool parsed = this->tryParse(commandType, this->typeConversions, CommandDecoder::NUM_TYPE_CONVERSIONS);

		// If unsuccessfull, store remaining bytes in buffer as blob
		if (!parsed) {
			numberOfBytes = this->dumpAndCopyCharBuffer(bytes, bufferSize);
			this->commandBuffer->push(Command(CommandType::UNDEFINED, CommandAction::UNDEFINED, 0, bytes, numberOfBytes));
			return;
		}

		// If successfull, remove type chars from the buffer
		this->dumpCharBuffer(CommandDecoder::COMMAND_TYPE_LENGTH);
		bufferSize -= CommandDecoder::COMMAND_TYPE_LENGTH;

		// Try to parse the command action
		enum CommandAction commandAction;
		parsed = this->tryParse(commandAction, this->actionConversions, CommandDecoder::COMMAND_ACTION_LENGTH);

		if (!parsed) {
			// If unsuccessfull, store remaining bytes in buffer as blob
			numberOfBytes = this->dumpAndCopyCharBuffer(bytes, bufferSize);
			this->commandBuffer->push(Command(commandType, CommandAction::UNDEFINED, 0, bytes, numberOfBytes));
			return;
		}

		// If successfull, remove action chars from the buffer
		this->dumpCharBuffer(CommandDecoder::COMMAND_ACTION_LENGTH);
		bufferSize -= CommandDecoder::COMMAND_ACTION_LENGTH;
		
		// Try to parse and integer from the data
		int numericData;
		numberOfBytes = this->copyCharBuffer(bytes, bufferSize);
		parsed = Util::Math::tryParseInt(numericData, bytes, numberOfBytes);
		delete[] bytes;
		bytes = nullptr;

		// If successfull, store integer and remove bytes from buffer
		if (parsed) {
			this->commandBuffer->push(Command(commandType, commandAction, numericData));
			this->charBuffer->clear();
		}
		else {
			// If unsuccessful, store data chars as blob data
			numberOfBytes = this->dumpAndCopyCharBuffer(bytes, bufferSize);
			this->commandBuffer->push(Command(commandType, commandAction, 0, bytes, numberOfBytes));
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

// Copies and stores a specified number of characters in the result
const int CommandDecoder::copyCharBuffer(char*& result, const int numberOfChars) const {
	if (numberOfChars <= 0) {
		return 0;
	}

	// Only initialize array if there are characters to copy
	int maxLength = Util::Math::min(numberOfChars, this->charBuffer->size());
	if (maxLength <= 0) {
		return 0;
	}

	// Copy buffer contents into a byte array
	result = new char[maxLength];
	for (int i = 0; i < maxLength; ++i) {
		result[i] = *this->charBuffer->get(i);
	}

	return maxLength;
}

// Removes and stores a specified number of characters from buffer in the result
const int CommandDecoder::dumpAndCopyCharBuffer(char*& result, const int numberOfChars) {
	const int actualNumberOfChars = this->copyCharBuffer(result, numberOfChars);
	dumpCharBuffer(actualNumberOfChars);
	return actualNumberOfChars;
}

// Removes specified number of characters from buffer
void CommandDecoder::dumpCharBuffer(const int numberOfChars) {
	const int size = this->charBuffer->size();

	if (numberOfChars == size) {
		this->charBuffer->clear();
	}
	else {
		// Remove select number of characters
		int maxLength = Util::Math::min(numberOfChars, size);
		for (int i = 0; i < maxLength; ++i) {
			delete this->charBuffer->pop();
		}
	}
}
#include "CommandController.h"

CommandController::CommandController() {
	// Add buffer for every movement command type value in the enum (except for UNDEFINED and ADMIN)
	int count = this->getCommandTypeCount();
	for (int i = 0; i < count; ++i) {
		this->bufferEnumMaps[i].type = (CommandTypeEnum)(i + 1);
		if (this->bufferEnumMaps[i].type == CommandTypeEnum::ADMIN) {
			this->bufferEnumMaps[i].frequencyTimer.set(0);
		}
	}
}

CommandController::~CommandController() {}

// Sets duration for buffer timer and starts it (timer determines frequency of command execution)
// ADMIN buffer wait is always set to 0
// For non-ADMIN buffers, if duration is less than zero, uses default wait
void CommandController::setMovementCommandDuration(const int duration) {
	int count = this->getCommandTypeCount();
	for (int i = 0; i < count; ++i) {
		if (this->bufferEnumMaps[i].type != CommandTypeEnum::ADMIN) {
			this->bufferEnumMaps[i].frequencyTimer.set(duration < 0 ? DEFAULT_MOVEMENT_COMMAND_DURATION : duration);
		}
	}
}

// Sets duration for char buffer timer, which determines how long to wait for new chars before clearing buffer
void CommandController::setCharBufferClearTimeout(const int duration) {
	this->charBufferClearTimer.set(duration < 0 ? DEFAULT_CHAR_BUFFER_CLEAR_DURATION : duration);
}

void CommandController::setDefaultCommand(const Command& command) {
	this->defaultCommand = command;
}

// Adds character array to command decoder and tries to parse commands
void CommandController::addChars(const unsigned long currentTime, const char* chars, const int length) {
	if (chars == nullptr || length <= 0) {
		return;
	}

	// If character receiving timed out, clear buffer
	if (this->charBufferClearTimer.isStopped() || this->charBufferClearTimer.isElapsed(currentTime)) {
		this->encounteredStart = false;
		this->charBuffer.clear();
		this->charBufferClearTimer.start(currentTime);
	}

	for (int i = 0; i < length; ++i) {
		if (chars[i] == COMMAND_START) { // If start character, remove all previous characters from buffer and add
			this->charBuffer.clear();
			this->charBuffer.push(chars[i]);
			this->encounteredStart = true;
		}
		else if (chars[i] == COMMAND_END) { // If end character, try to parse command from existing chars in buffer
			// If invalid sequence of symbols (end character w/o start, or just single end character), dump char buffer
			if (this->charBuffer.isEmpty() || !this->encounteredStart) {
				this->charBuffer.clear();
				return;
			}
			this->charBuffer.push(chars[i]);
			this->encounteredStart = false;

			// Extract next command chars from buffer
			char* bufferChars;
			int bufferCharsLength = this->dumpCharBuffer(bufferChars);

			// Try to parse command and add to buffer if successful
			Command command;
			if (command.tryParse(bufferChars, bufferCharsLength)) {
				this->insertCommand(currentTime, command);
			}

			delete[] bufferChars;
		}
		else { // If insignificant character, simply add it to buffer
			this->charBuffer.push(chars[i]);
		}
	}
}

// Stores contents of char buffer as array and clears buffer
// Returns number of chars read
const int CommandController::dumpCharBuffer(char*& chars) {
	const int length = this->charBuffer.size();
	chars = new char[length];
	for (int i = 0; i < length; ++i) {
		chars[i] = *this->charBuffer.get(i);
	}
	this->charBuffer.clear();
	return length;
}

// Goes through each command buffer, in order of appearance in CommandTypeEnum, and returns next command that is ready to be executed.
// ADMIN commands are always ready to be executed if available
// Movement commands are executed after timeout (based on a time quantum)
const Command* CommandController::next(const unsigned long currentTime) {
	int count = this->getCommandTypeCount();
	for (int i = 0; i < count; ++i) {
		// Return next command if frequency timer has elapsed and buffer contains command
		if (this->bufferEnumMaps[i].buffer.peek() != nullptr && (this->bufferEnumMaps[i].frequencyTimer.isStopped() || this->bufferEnumMaps[i].frequencyTimer.isElapsed(currentTime))) {
			// Reset command buffer timer
			this->bufferEnumMaps[i].frequencyTimer.start(currentTime);
			
			// Also set default command frequency timer so that it doesn't get returned as soon as next() gets called again
			const Command* result = this->bufferEnumMaps[i].buffer.pop();
			if (result->type() != CommandTypeEnum::ADMIN) {
				this->defaultCommandFrequencyTimer.start(currentTime);
			}
			return result;
		}
	}

	// No commands exist (or are ready to be retrieved)
	if (this->defaultCommandFrequencyTimer.isStopped() || this->defaultCommandFrequencyTimer.isElapsed(currentTime)) {
		this->defaultCommandFrequencyTimer.start(currentTime);
		return &defaultCommand;
	}
	else {
		return nullptr;
	}
}

// Inserts command into correct buffer. If command action is different from the one in the buffer, the buffer gets cleared before insertion (only for non-ADMIN command types).
void CommandController::insertCommand(unsigned long currentTime, Command& command) {
	if (command.type() == CommandTypeEnum::UNDEFINED || command.action() == CommandActionEnum::UNDEFINED) {
		return;
	}

	// Find buffer with same command type and insert command
	int count = this->getCommandTypeCount();
	for (int i = 0; i < count; ++i) {
		if (this->bufferEnumMaps[i].type == command.type()) {
			// Clear buffer for non-ADMIN command types, if buffer contains commands with different action
			if (command.type() != CommandTypeEnum::ADMIN && !this->bufferEnumMaps[i].buffer.isEmpty() && this->bufferEnumMaps[i].buffer.peek()->action() != command.action()) {
				this->bufferEnumMaps[i].buffer.clear();
			}
			this->bufferEnumMaps[i].buffer.push(command);
		}
	}
}

// Returns number of movement command types
int CommandController::getCommandTypeCount() const {
	return 	(int)CommandTypeEnum::Count - 1;
}
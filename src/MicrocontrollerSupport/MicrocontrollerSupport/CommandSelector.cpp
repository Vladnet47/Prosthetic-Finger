#include "CommandSelector.h"

// Takes command selection specifications
CommandSelector::CommandSelector(const SelectionOptions& options) {
	this->buffer = new Queue<Command>(options.bufferSize, options.replaceOld);
}

CommandSelector::~CommandSelector() {
	delete this->buffer;
}

// Adds command to buffer
void CommandSelector::add(const Command* command) {
	this->buffer->push(command);
}

// Returns next command to execute
Command* CommandSelector::next() {
	return this->buffer->popFront();
}

// Clears command buffer
void CommandSelector::clear() {
	this->buffer->clear();
}

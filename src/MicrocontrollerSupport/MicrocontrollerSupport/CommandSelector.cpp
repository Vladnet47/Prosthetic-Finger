#include "CommandSelector.h"

// Takes command selection specifications
CommandSelector::CommandSelector(const SelectionOptions& options) {
	this->buffer = new Queue<Command>(options.bufferSize, options.replaceOld);
}

CommandSelector::~CommandSelector() {
	delete this->buffer;
}

// Adds command to buffer
void CommandSelector::add(const Command& command) {
	this->buffer->push(command);
}

// Returns next command to execute
const Command* CommandSelector::next() {
	return this->buffer->popFront();
}

// Returns command at given index of buffer
const Command* CommandSelector::get(const int index) const {
	return this->buffer->get(index);
}

// Clears command buffer
void CommandSelector::clear() {
	this->buffer->clear();
}

// Returns number of commands currently in buffer
int CommandSelector::size() const {
	return this->buffer->size();
}

bool CommandSelector::isEmpty() const {
	return this->buffer->isEmpty();
}

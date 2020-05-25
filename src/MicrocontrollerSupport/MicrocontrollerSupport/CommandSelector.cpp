#include "CommandSelector.h"

CommandSelector::CommandSelector() {
	// Add buffer for every command type value in the enum (except for UNDEFINED)
	this->commandBuffers = new BufferEnumMap[NUM_TYPES];
	for (int i = 0; i < NUM_TYPES; ++i) {
		this->commandBuffers[i].type = (CommandType)(i + 1);
		this->commandBuffers[i].buffer = new ElasticBuffer<Command>();
	}
}

CommandSelector::~CommandSelector() {
	delete[] this->commandBuffers;
}

// Adds non-undefined command to proper buffer
void CommandSelector::add(const Command& command) {
	if (command.type() != CommandType::UNDEFINED && command.action() != CommandAction::UNDEFINED) {
		Buffer<Command>* buffer = this->getBuffer(command.type());
		if (buffer != nullptr) {
			buffer->push(command);
		}
	}
}

// Returns true if instant buffer contains command
const bool CommandSelector::hasNext(const enum CommandType type) const {
	const Buffer<Command>* buffer = this->getBuffer(type);
	return buffer != nullptr && !buffer->isEmpty();
}

// Returns first command from instant buffer or nullptr if none exist
const Command* CommandSelector::next(const enum CommandType type) {
	Buffer<Command>* buffer = this->getBuffer(type);
	if (buffer != nullptr) {
		return buffer->pop();
	}

	return nullptr;
}

// Returns pointer to buffer with commands for given command type
Buffer<Command>* CommandSelector::getBuffer(const enum CommandType type) const {
	for (int i = 0; i < NUM_TYPES; ++i) {
		if (this->commandBuffers[i].type == type) {
			return this->commandBuffers[i].buffer;
		}
	}

	return nullptr;
}
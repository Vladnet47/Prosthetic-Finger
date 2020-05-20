#include "CommandBuffer.h"

// Initialized with a size (number of commands in buffer) and options:
	//     prioritizeNew - if true, buffer replaces oldest command when it is full. Otherwise, discard the new one.
CommandBuffer::CommandBuffer(int size, bool prioritizeNew) {
	this->commandList = new Command[size];
	this->maxSize = size < 1 ? 1 : size;
	this->prioritizeNew = prioritizeNew;

	this->clear();
}

CommandBuffer::~CommandBuffer() {
	delete[] this->commandList;
}

// Returns command at given index, or nullptr if index is out of bounds
Command* CommandBuffer::get(int index) const {
	if (this->isEmpty() || index < 0 || index >= this->size()) {
		return nullptr;
	}

	int convertedIndex = this->incrementIndex(this->start, index);

	return new Command{ this->commandList[convertedIndex].type, this->commandList[convertedIndex].data };
}

// Returns next command in buffer, or none
Command* CommandBuffer::peek() const {
	if (this->isEmpty()) {
		return nullptr;
	}

	return new Command{ this->commandList[this->start].type, this->commandList[this->start].data };
}

// Returns 
Command* CommandBuffer::pop() {
	Command* result = this->peek();

	if (result != nullptr) {
		this->currentSize--;
		this->start = this->incrementIndex(this->start);
	}

	return result;
}

void CommandBuffer::push(int type, int data) {
	bool isFull = this->size() == this->maxSize;

	if (isFull && !this->prioritizeNew) {
		return;
	}

	this->commandList[this->end].type = type;
	this->commandList[this->end].data = data;
	this->end = this->incrementIndex(this->end);

	if (isFull) {
		this->start = this->incrementIndex(this->start);
	}
	else {
		this->currentSize++;
	}
}

void CommandBuffer::clear() {
	this->currentSize = 0;
	this->start = 0;
	this->end = 0;
}

int CommandBuffer::size() const {
	return this->currentSize < 0 ? 0 : this->currentSize;
}

bool CommandBuffer::isEmpty() const {
	return this->size() == 0;
}

Command* CommandBuffer::list() const {
	Command* result = new Command[this->size()];

	int commandIndex = this->start;
	for (int i = 0; i < this->size(); ++i) {
		commandIndex = this->incrementIndex(this->start, i);
		result[i].type = this->commandList[commandIndex].type;
		result[i].data = this->commandList[commandIndex].data;
	}

	return result;
}

int CommandBuffer::incrementIndex(int index, int amount) const {
	return (index + amount) % this->maxSize;
}
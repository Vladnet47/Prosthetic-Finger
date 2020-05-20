#pragma once

// Command sent to microcontroller
struct Command {
	int type;
	int data;
};

// Types of defined commands
enum CommandType {
	DEFAULT,
	CONTRACT_HAND,
	EXTEND_HAND,
};

// Buffer that keeps track of a specified number of incoming commands
class CommandBuffer {
public:
	// Initialized with a size (number of commands in buffer) and options:
	//     prioritizeNew - if true, buffer replaces oldest command when it is full. Otherwise, discard the new one.
	CommandBuffer(int size, bool prioritizeNew = true) {
		this->commandList = new Command[size];
		this->start = 0;
		this->end = 0;
		this->currentSize = 0;
		this->maxSize = !size ? 1 : size;
		this->prioritizeNew = prioritizeNew;
	}

	~CommandBuffer() {
		delete[] this->commandList;
	}

	Command* peek() {
		if (this->isEmpty()) {
			return nullptr;
		}

		return new Command{ this->commandList[this->start].type, this->commandList[this->start].data };
	}

	Command* pop() {
		Command* result = this->peek();

		if (result != nullptr) {
			this->currentSize--;
			this->start = this->incrementIndex(this->start);
		}

		return result;
	}

	void push(int type, int data = 0) {
		bool isFull = this->currentSize == this->maxSize;

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

	void clear() {
		this->currentSize = 0;
		this->start = 0;
		this->end = 0;
	}

	int size() {
		return this->currentSize;
	}

	bool isEmpty() {
		return currentSize <= 0;
	}

	Command* list() {
		Command* result = new Command[this->currentSize];

		int commandIndex = this->start;
		for (int i = 0; i < this->currentSize; ++i) {
			commandIndex = this->incrementIndex(this->start, i);
			result[i].type = this->commandList[commandIndex].type;
			result[i].data = this->commandList[commandIndex].data;
		}

		return result;
	}

private:
	Command* commandList;
	int start;
	int end;

	int currentSize;
	int maxSize;

	bool prioritizeNew;

	int incrementIndex(int index, int amount = 1) {
		return (currentSize >= 0) ? (index + amount) % maxSize : 0;
	}
};
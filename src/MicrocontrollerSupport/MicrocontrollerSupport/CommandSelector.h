#pragma once

#include "Queue.h"
#include "Command.h"

struct SelectionOptions {
	SelectionOptions(const int bufferSize, const bool replaceOld = true) {
		this->bufferSize = bufferSize;
		this->replaceOld = replaceOld;
	}

	int bufferSize;
	bool replaceOld;
};

class CommandSelector {
public:
	CommandSelector(const SelectionOptions& options);
	~CommandSelector();
	void add(const Command* command);
	Command* next();
	void clear();
private:
	Queue<Command>* buffer;
};

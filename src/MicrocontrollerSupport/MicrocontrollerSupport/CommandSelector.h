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
	void add(const Command& command);
	const Command* next();
	const Command* get(const int index) const;
	void clear();
	int size() const;
	bool isEmpty() const;
private:
	Queue<Command>* buffer;
};

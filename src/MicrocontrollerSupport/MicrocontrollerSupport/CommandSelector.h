#pragma once
#include "Command.h"
#include "ElasticBuffer.h"

// Used to organize commands by type and determines which commands to execute
class CommandSelector {
public:
	CommandSelector();
	~CommandSelector();
	void add(const Command& command);
	const bool hasNext(const enum CommandType type) const;
	const Command* next(const enum CommandType type);
private:
	struct BufferEnumMap {
		Buffer<Command>* buffer;
		enum CommandType type;

		BufferEnumMap(const enum CommandType type = CommandType::UNDEFINED, Buffer<Command>* buffer = nullptr) {
			this->type = type;
			this->buffer = buffer;
		}
		~BufferEnumMap() {
			delete this->buffer;
		}
	};

	BufferEnumMap* commandBuffers;

	Buffer<Command>* getBuffer(const enum CommandType type) const;
};
#pragma once
#include "CommandConfig.h"
#include "Command.h"
#include "Timer.h"
#include "Buffer.h"

// Used to organize commands by type and determines which commands to execute
class CommandController {
public:
	CommandController();
	~CommandController();
	void setMovementCommandDuration(const int duration);
	void setCharBufferClearTimeout(const int duration);
	void setDefaultCommand(const Command& command);
	void addChars(const unsigned long currentTime, const char* chars, const int length);
	const Command* next(const unsigned long currentTime);
private:
	struct BufferEnumMap {
		enum CommandTypeEnum type;
		Buffer<Command, MAX_COMMANDS_IN_BUFFER> buffer{};
		Timer frequencyTimer{ DEFAULT_MOVEMENT_COMMAND_DURATION };

		BufferEnumMap() {
			this->type = CommandTypeEnum::UNDEFINED;
		}
		~BufferEnumMap() {}
	};

	// Movement command buffers
	BufferEnumMap bufferEnumMaps[(int)CommandTypeEnum::Count - 1];
	Command defaultCommand{ CommandTypeEnum::FINGER_ALL, CommandActionEnum::STOP };
	Timer defaultCommandFrequencyTimer{ DEFAULT_MOVEMENT_COMMAND_DURATION };

	// Character buffer
	Buffer<char, MAX_CHARACTERS_IN_BUFFER> charBuffer{};
	Timer charBufferClearTimer{ DEFAULT_CHAR_BUFFER_CLEAR_DURATION };
	bool encounteredStart;
	
	const int dumpCharBuffer(char*& chars);
	void insertCommand(unsigned long currentTime, Command& command);
	int getCommandTypeCount() const;
};
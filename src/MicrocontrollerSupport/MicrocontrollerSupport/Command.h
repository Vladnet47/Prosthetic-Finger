#pragma once

const int NUM_TYPES = 7;
const int NUM_ACTIONS = 4;

// Type of command (what it is referring to)
enum class CommandType {
	UNDEFINED,

	ADMIN,

	FINGER_ALL,
	FINGER_INDEX,
	FINGER_MIDDLE,
	FINGER_RING,
	FINGER_LITTLE,
	FINGER_THUMB
};

// Actions of commands
enum class CommandAction {
	UNDEFINED,

	LIST_BUFFER,

	STOP,
	CONTRACT,
	EXTEND
};

class Command {
public:
	Command(enum CommandType commandType = CommandType::UNDEFINED, enum CommandAction commandAction = CommandAction::UNDEFINED, int numericData = 0, const char blobData[] = nullptr, int blobLength = 0);
	Command(const Command& other);
	~Command();

	const enum CommandType type() const;
	const enum CommandAction action() const;
	const int nData() const;
	const char* bData() const;
	const int bLength() const;

	Command& operator=(const Command& other);
	const bool operator==(const Command& other) const;
	const bool operator!=(const Command& other) const;

private:
	enum CommandType commandType;
	enum CommandAction commandAction;
	int numericData;
	const char* blobData;
	int blobLength;

	void clear();
};

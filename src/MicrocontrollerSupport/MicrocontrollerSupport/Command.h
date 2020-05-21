#pragma once

// Types of defined commands
enum CommandType {
	UNDEFINED,

	LIST_BUFFER,

	STOP,
	CONTRACT_HAND,
	EXTEND_HAND
};

class Command {
public:
	Command(enum CommandType commandType = UNDEFINED, int numericData = 0, char* blobData = nullptr, int chars = 0);
	Command(const Command& other);
	~Command();

	enum CommandType type() const;
	int nData() const;
	char* bData() const;
	int bLength() const;
	void operator=(const Command& other);
	bool operator==(const Command& other) const;
	bool operator!=(const Command& other) const;

private:
	enum CommandType commandType;
	int numericData;
	char* blobData;
	int blobLength;

	inline void clear();
};

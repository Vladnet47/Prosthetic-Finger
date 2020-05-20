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
	Command(int commandType = UNDEFINED, int numericData = 0, char* blobData = nullptr);
	Command(const Command& other);
	~Command();

	inline int type() const;
	inline int nData() const;
	inline char* bData() const;
private:
	int commandType;
	int numericData;
	char* blobData;

	inline void clear();
};

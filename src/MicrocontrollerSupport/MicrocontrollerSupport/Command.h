#pragma once
#include <cstring>
//#include <Arduino.h>

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
	Command(int commandType = UNDEFINED, int numericData = 0, char* blobData = nullptr, int chars = 0);
	Command(const Command& other);
	~Command();

	int type() const;
	int nData() const;
	char* bData() const;
	int bLength() const;
	void operator=(const Command& other);
	bool operator==(const Command& other) const;
	bool operator!=(const Command& other) const;

private:
	int commandType;
	int numericData;
	char* blobData;
	int blobLength;

	inline void clear();
};

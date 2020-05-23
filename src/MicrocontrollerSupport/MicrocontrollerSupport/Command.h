#pragma once
#include "CommandType.h"

class Command {
public:
	Command(enum CommandType commandType = UNDEFINED, int numericData = 0, const char* blobData = nullptr, int blobLength = 0);
	Command(const Command& other);
	~Command();

	enum CommandType type() const;
	int nData() const;
	const char* bData() const;
	int bLength() const;

	void operator=(const Command& other);
	bool operator==(const Command& other) const;
	bool operator!=(const Command& other) const;

private:
	enum CommandType commandType;
	int numericData;
	const char* blobData;
	int blobLength;

	void clear();
};

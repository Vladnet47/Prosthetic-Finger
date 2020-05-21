#include "Command.h"

Command::Command(enum CommandType commandType, int numericData, char* blobData, int chars) {
	this->commandType = commandType;
	this->numericData = numericData;
	this->blobData = blobData;
	this->blobLength = chars;
}

Command::Command(const Command& other) {
	*this = other;

	// this->commandType = other.commandType;
	// this->numericData = other.numericData;
	// this->blobData = other.blobData;
}

Command::~Command() {
	this->clear();
}

enum CommandType Command::type() const {
	return this->commandType;
}

int Command::nData() const {
	return this->numericData;
}

char* Command::bData() const {
	return this->blobData;
}

int Command::bLength() const {
	return this->blobLength;
}

void Command::clear() {
	delete this->blobData;
	this->commandType = UNDEFINED;
	this->numericData = 0;
}

void Command::operator=(const Command& other) {
	delete[] this->blobData;

	this->commandType = other.type();
	this->numericData = other.nData();
	this->blobLength = other.bLength();

	this->blobData = new char[this->blobLength];
	char* otherBlobData = other.bData();
	for (int i = 0; i < this->blobLength; ++i) {
		this->blobData[i] = otherBlobData[i];
	}
}

bool Command::operator==(const Command& other) const {
	return this->type() == other.type() && this->nData() == other.nData();
}

bool Command::operator!=(const Command& other) const {
	return !(*this == other);
}

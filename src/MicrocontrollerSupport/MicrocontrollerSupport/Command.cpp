#include "Command.h"

Command::Command(int commandType, int numericData, char* blobData) {
	this->commandType = commandType;
	this->numericData = numericData;
	this->blobData = blobData;
}

Command::Command(const Command& other) {
	this->clear();

	this->commandType = other.commandType;
	this->numericData = other.numericData;
	this->blobData = other.blobData;
}

Command::~Command() {
	this->clear();
}

int Command::type() const {
	return this->commandType;
}

int Command::nData() const {
	return this->numericData;
}

char* Command::bData() const {
	return this->blobData;
}

void Command::clear() {
	delete this->blobData;
	this->commandType = UNDEFINED;
	this->numericData = 0;
}

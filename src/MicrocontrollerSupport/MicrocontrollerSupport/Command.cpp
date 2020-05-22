#include "Command.h"

Command::Command(enum CommandType commandType, int numericData, char* blobData, int blobLength) {
	this->commandType = commandType;
	this->numericData = numericData;
	this->blobData = blobData;
	this->blobLength = blobLength;
}

Command::Command(const Command& other) {
	*this = other;
}

Command::~Command() {
	this->clear();
}

// Returns command type
enum CommandType Command::type() const {
	return this->commandType;
}

// Returns numerical command data
int Command::nData() const {
	return this->numericData;
}

// Returns blob command data
const char* Command::bData() const {
	return this->blobData;
}

// Returns length of blob command data
int Command::bLength() const {
	return this->blobLength;
}

// Removes all command data and sets to UNDEFINED
void Command::clear() {
	delete[] this->blobData;
	this->commandType = UNDEFINED;
	this->numericData = 0;
	this->blobData = 0;
}

// Sets object data equal to other
void Command::operator=(const Command& other) {
	this->clear();

	// Copy all primitive types
	this->commandType = other.type();
	this->numericData = other.nData();
	this->blobLength = other.bLength();

	// Copy blob data
	this->blobData = new char[this->blobLength];
	const char* otherBlobData = other.bData();
	for (int i = 0; i < this->blobLength; ++i) {
		this->blobData[i] = otherBlobData[i];
	}
}

// Returns true if all object data is the same, false otherwise
bool Command::operator==(const Command& other) const {
	// Verify that all primitive types match
	if (this->type() != other.type() || this->nData() != other.nData() || this->bLength() != other.bLength()) {
		return false;
	}

	const char* otherData = other.bData();

	// Verify that blob data matches
	for (int i = 0; i < this->bLength(); ++i) {
		if (this->blobData[i] != otherData[i]) {
			return false;
		}
	}

	return true;
}

// Returns true if object data does not match, false otherwise
bool Command::operator!=(const Command& other) const {
	return !(*this == other);
}

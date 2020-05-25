#include "Command.h"

Command::Command(enum CommandType commandType, enum CommandAction commandAction, int numericData, const char blobData[], int blobLength) {
	this->commandType = commandType;
	this->commandAction = commandAction;
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
const enum CommandType Command::type() const {
	return this->commandType;
}

// Returns command action
const enum CommandAction Command::action() const {
	return this->commandAction;
}

// Returns numerical command data
const int Command::nData() const {
	return this->numericData;
}

// Returns blob command data
const char* Command::bData() const {
	return this->blobData;
}

// Returns length of blob command data
const int Command::bLength() const {
	return this->blobLength;
}

// Removes all command data and sets to UNDEFINED
void Command::clear() {
	if (this->blobLength > 0 && this->blobData != nullptr) {
		delete[] this->blobData;
	}
	
	this->commandAction = CommandAction::UNDEFINED;
	this->commandType = CommandType::UNDEFINED;
	this->numericData = 0;
	this->blobData = 0;
	this->blobLength = 0;
}

// Sets object data equal to other
Command& Command::operator=(const Command& other) {
	if (this != &other) {
		this->clear();

		// Copy all primitive types
		this->commandType = other.type();
		this->commandAction = other.action();
		this->numericData = other.nData();
		this->blobLength = other.bLength();

		if (this->blobLength != 0 && other.bData() != nullptr) {
			// Copy blob data
			char* newBlobData = new char[this->blobLength];
			const char* otherBlobData = other.bData();
			for (int i = 0; i < this->blobLength; ++i) {
				newBlobData[i] = otherBlobData[i];
			}

			this->blobData = newBlobData;
		}
	}

	return *this;
}

// Returns true if all object data is the same, false otherwise
const bool Command::operator==(const Command& other) const {
	// Verify that all primitive types match
	if (this->action() != other.action() || this->nData() != other.nData() || this->bLength() != other.bLength()) {
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
const bool Command::operator!=(const Command& other) const {
	return !(*this == other);
}

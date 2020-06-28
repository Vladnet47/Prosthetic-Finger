#pragma once
#include "CommandConfig.h"

template <class T>
// Used to map between raw characters sent to the microcontroller and pre-defined commands
class EnumMap {
public:
	EnumMap(const char chars[], const int length, const T value);
	~EnumMap();
	const bool tryParse(T& result, const char chars[MAX_CHARACTERS_IN_BUFFER], const int length, const int start, const int end) const;
private:
	const char* characters;
	int numCharacters;
	T enumValue;
};

template <class T>
EnumMap<T>::EnumMap(const char chars[], const int length, const T enumValue) {
	this->numCharacters = chars == nullptr ? 0 : length;
	this->characters = chars;
	this->enumValue = enumValue;
}

template <class T>
EnumMap<T>::~EnumMap() {
	delete this->characters;
}

template <class T>
// Returns true and sets result to enum value if given char array matches this conversion
const bool EnumMap<T>::tryParse(T& result, const char chars[MAX_CHARACTERS_IN_BUFFER], const int length, const int start, const int end) const {
	if (length < 0 || end - start != this->numCharacters) {
		return false;
	}

	for (int i = 0; i < this->numCharacters; ++i) {
		if (this->characters[i] != chars[start + i]) {
			return false;
		}
	}

	result = this->enumValue;
	return true;
}

extern EnumMap<CommandTypeEnum>* COMMAND_TYPE_CONVERSIONS;
extern EnumMap<CommandActionEnum>* COMMAND_ACTION_CONVERSIONS;
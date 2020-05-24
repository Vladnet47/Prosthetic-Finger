#pragma once

template <class T>
// Used to map between raw characters sent to the microcontroller and pre-defined commands
class EnumMap {
public:
	EnumMap(const char chars[], const int length, const T value);
	~EnumMap();
	const bool tryParse(T& result, const char chars[], const int length) const;
	const int length() const;
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
const bool EnumMap<T>::tryParse(T& result, const char chars[], const int length) const {
	if (length != this->numCharacters) {
		return false;
	}

	for (int i = 0; i < length; ++i) {
		if (this->characters[i] != chars[i]) {
			return false;
		}
	}

	result = this->enumValue;
	return true;
}

template <class T>
const int EnumMap<T>::length() const {
	return this->numCharacters;
}
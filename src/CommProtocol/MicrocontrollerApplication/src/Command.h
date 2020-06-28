#pragma once
#include "CommandConfig.h"
#include "CommandConversions.h"

class Command {
public:
	explicit Command();
	Command(enum CommandTypeEnum CommandTypeEnum, enum CommandActionEnum CommandActionEnum, int numericData = 0);
	Command(const Command& other);
	~Command();

	const bool tryParse(const char chars[MAX_CHARACTERS_IN_BUFFER], const int length);
	const enum CommandTypeEnum type() const;
	const enum CommandActionEnum action() const;
	const int data() const;

	Command& operator=(const Command& other);
	const bool operator==(const Command& other) const;
	const bool operator!=(const Command& other) const;

private:
	enum CommandTypeEnum commandType;
	enum CommandActionEnum commandAction;
	int numericData;

	template <class T>
	const bool tryParseEnum(T& result, const char chars[MAX_CHARACTERS_IN_BUFFER], const int length, const int start, const int end, const EnumMap<T>* conversions, const int numConversions);
	const bool tryParseInteger(int& result, const char chars[MAX_CHARACTERS_IN_BUFFER], const int length, const int start, const int end) const;
	const int exponent(const int base, const int exp) const;
};

// Tries to parse enum value from the next bytes in buffer. Returns true and sets result to parsed value if successful, returns false and leaves result in undefined state otherwise
template <class T>
const bool Command::tryParseEnum(T& result, const char chars[MAX_CHARACTERS_IN_BUFFER], const int length, const int start, const int end, const EnumMap<T>* conversions, const int numConversions) {
	if (chars != nullptr && length > 0 && numConversions > 0) {
		// Try to parse enum from chars using each conversion
		for (int i = 0; i < numConversions; ++i) {
			if (conversions[i].tryParse(result, chars, length, start, end)) {
				return true;
			}
		}
	}

	return false;
}

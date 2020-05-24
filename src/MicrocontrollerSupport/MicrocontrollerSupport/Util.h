#pragma once

namespace Util {
	namespace Math {
		static const int min(const int val1, const int val2);
		static const int max(const int val1, const int val2);
		static const int abs(const int val);
		static const int pow(const int base, const int exp);
		static const bool tryParseInt(int& result, const char chars[], const int length);
	}
}

// Returns min of two values
const int Util::Math::min(const int val1, const int val2) {
	return val1 < val2 ? val1 : val2;
}

// Returns max of two values
const int Util::Math::max(const int val1, const int val2) {
	return val1 > val2 ? val1 : val2;
}

// Returns absolute value of value
const int Util::Math::abs(const int val) {
	return val > 0 ? val : -val;
}

// Returns base to the power of exponent (1 if exp <= 0)
const int Util::Math::pow(const int base, const int exp) {
	int result = 1;
	for (int i = 0; i < exp; ++i) {
		result *= base;
	}
	return result;
}

// Returns true if successfully parsed integer from the character buffer and sets result equal to that integer.
// Otherwise, returns false and leaves result integer in undefined state
const bool Util::Math::tryParseInt(int& result, const char chars[], const int length) {
	// Return false if empty
	if (chars == nullptr || length == 0) {
		return false;
	}

	result = 0;

	// Inspect every character in array from the back
	for (int i = length - 1; i >= 0; --i) {
		// If '-' character, it must be the first in the list
		if (chars[i] == '-' && i == 0) {
			result *= -1;
		}
		// If numeric, convert to integer
		else if (chars[i] == '0' || chars[i] == '1' || chars[i] == '2' || chars[i] == '3' || chars[i] == '4' || 
			chars[i] == '5' || chars[i] == '6' || chars[i] == '7' || chars[i] == '8' || chars[i] == '9') {
			result += (chars[i] - '0') * Util::Math::pow(10, length - i - 1);
		}
		// Character not numeric, or '-' character in wrong place
		else {
			return false;
		}
	}

	return true;
}
#pragma once

namespace Util {
	namespace Math {
		static const int min(const int val1, const int val2);
		static const int max(const int val1, const int val2);
		static const int abs(const int val);
		static const int pow(const int base, const int exp);
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
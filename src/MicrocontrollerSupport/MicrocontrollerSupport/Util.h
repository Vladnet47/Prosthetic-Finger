#pragma once

namespace Util {
	namespace Math {
		static const int min(const int val1, const int val2);
		static const int max(const int val1, const int val2);
		static const int abs(const int val);
		static const int pow(const int base, const int exp);
	}
}

const int Util::Math::min(const int val1, const int val2) {
	return val1 < val2 ? val1 : val2;
}

const int Util::Math::max(const int val1, const int val2) {
	return val1 > val2 ? val1 : val2;
}

const int Util::Math::abs(const int val) {
	return val > 0 ? val : -val;
}

const int Util::Math::pow(const int base, const int exp) {
	int result = 1;
	for (int i = 0; i < exp; ++i) {
		result *= base;
	}
	return result;
}
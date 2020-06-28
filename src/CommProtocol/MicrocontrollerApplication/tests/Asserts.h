#pragma once
#include <string>
#include <iostream>

using namespace std;

namespace Asserts {
	static const bool ONLY_ERRORS = true;
	static void AssertTrue(string message, bool value);
	static void AssertFalse(string message, bool value);
	template <class T>
	static void AssertEqual(string message, T value1, T value2);
	template <class T>
	void AssertNotEqual(string message, T value1, T value2);
	template <class T>
	void AssertNull(string message, T* value);
}

void Asserts::AssertTrue(string message, bool value) {
	if (value) {
		if (!ONLY_ERRORS) {
			cout << message << "...passed" << endl;
		}
	}
	else {
		cout << message << "...FAILED" << endl;
	}
}

void Asserts::AssertFalse(string message, bool value) {
	if (!value) {
		if (!ONLY_ERRORS) {
			cout << message << "...passed" << endl;
		}
	}
	else {
		cout << message << "...FAILED" << endl;
	}
}

template <class T>
void Asserts::AssertEqual(string message, T value1, T value2) {
	if (value1 == value2) {
		if (!ONLY_ERRORS) {
			cout << message << "...passed" << endl;
		}
	}
	else {
		cout << message << "...FAILED" << endl;
	}
}

template <class T>
void Asserts::AssertNotEqual(string message, T value1, T value2) {
	if (value1 != value2) {
		if (!ONLY_ERRORS) {
			cout << message << "...passed" << endl;
		}
	}
	else {
		cout << message << "...FAILED" << endl;
	}
}

template <class T>
void Asserts::AssertNull(string message, T* value) {
	if (value == nullptr) {
		if (!ONLY_ERRORS) {
			cout << message << "...passed" << endl;
		}
	}
	else {
		cout << message << "...FAILED" << endl;
	}
}
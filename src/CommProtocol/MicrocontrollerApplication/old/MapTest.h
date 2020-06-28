#pragma once
#include <iostream>
#include <string>
#include "Asserts.h"
#include "Command.h"
#include "CommandConfig.h"
#include "Map.h"

namespace MapTest {
	static void Run();
	static void ConstructorTest();
	static void InsertTest();
	static void GetTest();
	static void ReplaceTest();
	static void OverflowTest();
}

void MapTest::Run() {
	MapTest::ConstructorTest();
	MapTest::InsertTest();
	MapTest::GetTest();
	MapTest::ReplaceTest();
	MapTest::OverflowTest();
}

void MapTest::ConstructorTest() {
	cout << "Constructor Test" << endl;
	Map<CommandTypeEnum, char[2], 10> map;
	Asserts::AssertEqual("1) Size is 0", map.size(), 0);
}

void MapTest::InsertTest() {
	cout << "Insert Test" << endl;
	Map<CommandTypeEnum, char*, 10> map;
	char* arr = new char[2]{ 'A', 'D' };
	map.insert(CommandTypeEnum::ADMIN, arr);
	Asserts::AssertEqual("1) Size is 1", map.size(), 1);
	Asserts::AssertTrue("2) Contains ADMIN", map.contains(CommandTypeEnum::ADMIN));
	delete[] arr;
}

void MapTest::GetTest() {
	cout << "Get Test" << endl;
	Map<CommandTypeEnum, char*, 10> map;
	char* arr = new char[2]{ 'A', 'D' };
	map.insert(CommandTypeEnum::ADMIN, arr);
	const char* value = *map.get(CommandTypeEnum::ADMIN);
	Asserts::AssertEqual("1) AD array retrieved", value[0], 'A');
	Asserts::AssertEqual("2) AD array retrieved", value[1], 'D');
	delete[] arr;
}

void MapTest::ReplaceTest() {
	cout << "Replace Test" << endl;
	Map<CommandTypeEnum, char*, 10> map;
	char* arr1 = new char[2]{ 'A', 'D' };
	char* arr2 = new char[2]{ 'S', 'E' };
	map.insert(CommandTypeEnum::ADMIN, arr1);
	map.insert(CommandTypeEnum::ADMIN, arr2);
	const char* value = *map.get(CommandTypeEnum::ADMIN);
	Asserts::AssertEqual("1) AD array retrieved", value[0], 'S');
	Asserts::AssertEqual("2) AD array retrieved", value[1], 'E');
	delete[] arr1;
	delete[] arr2;
}

void MapTest::OverflowTest() {
	cout << "Overflow Test" << endl;
	Map<CommandTypeEnum, char*, 1> map;
	char* arr1 = new char[2]{ 'A', 'D' };
	char* arr2 = new char[2]{ 'S', 'E' };
	map.insert(CommandTypeEnum::ADMIN, arr1);
	map.insert(CommandTypeEnum::FINGER_ALL, arr2);
	Asserts::AssertEqual("1) Size is 1", map.size(), 1);
	const char* value = *map.get(CommandTypeEnum::ADMIN);
	Asserts::AssertEqual("1) AD array retrieved", value[0], 'A');
	Asserts::AssertEqual("2) AD array retrieved", value[1], 'D');
	delete[] arr1;
	delete[] arr2;
}
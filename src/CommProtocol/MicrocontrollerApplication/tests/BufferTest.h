#pragma once
#include <iostream>
#include <string>
#include "Asserts.h"
#include "../src/CommandConfig.h"
#include "../src/Command.h"
#include "../src/Buffer.h"

namespace BufferTest {
	static void Run();
	static void ConstructorTest();
	static void ClearTest();
	static void PushPopTest();
	static void PushPopRotatingTest();
	static void PushGetPeekTest();
	static void BufferOverflowTest();
}

void BufferTest::Run() {
	BufferTest::ConstructorTest();
	BufferTest::ClearTest();
	BufferTest::PushPopTest();
	BufferTest::PushPopRotatingTest();
	BufferTest::PushGetPeekTest();
	BufferTest::BufferOverflowTest();
}

void BufferTest::ConstructorTest() {
	cout << "Testing Constructor" << endl;

	Buffer<char, 10> bufferChar;
	Asserts::AssertTrue("1) Buffer empty", bufferChar.isEmpty());
	Asserts::AssertEqual("2) Buffer size 0", bufferChar.size(), 0);

	Buffer<Command, 10> bufferCommand;
	Asserts::AssertTrue("3) Buffer empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("4) Buffer size 0", bufferCommand.size(), 0);
}

void BufferTest::ClearTest() {
	cout << "Testing Clear" << endl;

	Buffer<char, 10> bufferChar;
	bufferChar.push('a');
	bufferChar.push('b');
	bufferChar.clear();
	Asserts::AssertTrue("1) Buffer empty", bufferChar.isEmpty());
	Asserts::AssertEqual("2) Buffer size 0", bufferChar.size(), 0);

	Command command;
	Buffer<Command, 10> bufferCommand;
	bufferCommand.push(command);
	bufferCommand.push(command);
	bufferCommand.clear();
	Asserts::AssertTrue("3) Buffer empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("4) Buffer size 0", bufferCommand.size(), 0);
}

void BufferTest::PushPopTest() {
	cout << "Testing Push Pop" << endl;

	Buffer<char, 10> bufferChar;
	bufferChar.push('a');
	bufferChar.push('b');
	Asserts::AssertFalse("1) Buffer not empty", bufferChar.isEmpty());
	Asserts::AssertEqual("2) Buffer size 2", bufferChar.size(), 2);
	const char* resultChar = bufferChar.pop();
	Asserts::AssertEqual("3) Buffer pop equal 'a'", *resultChar, 'a');
	Asserts::AssertFalse("4) Buffer not empty", bufferChar.isEmpty());
	Asserts::AssertEqual("5) Buffer size 1", bufferChar.size(), 1);
	resultChar = bufferChar.pop();
	Asserts::AssertEqual("6) Buffer pop equal 'b'", *resultChar, 'b');
	Asserts::AssertTrue("7) Buffer empty", bufferChar.isEmpty());
	Asserts::AssertEqual("8) Buffer size 0", bufferChar.size(), 0);

	Command command1{ CommandTypeEnum::ADMIN, CommandActionEnum::SET_CHAR_BUFFER_CLEAR_TIMER, 10 };
	Command command2{ CommandTypeEnum::FINGER_ALL, CommandActionEnum::CONTRACT, 10 };
	Buffer<Command, 10> bufferCommand;
	bufferCommand.push(command1);
	bufferCommand.push(command2);
	Asserts::AssertFalse("9) Buffer not empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("10) Buffer size 2", bufferCommand.size(), 2);
	const Command* resultCommand = bufferCommand.pop();
	Asserts::AssertEqual("11) Type is admin", resultCommand->type(), CommandTypeEnum::ADMIN);
	Asserts::AssertEqual("12) Action is set char buffer timer", resultCommand->action(), CommandActionEnum::SET_CHAR_BUFFER_CLEAR_TIMER);
	Asserts::AssertEqual("13) Data is 10", resultCommand->data(), 10);
	Asserts::AssertFalse("14) Buffer not empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("15) Buffer size 1", bufferCommand.size(), 1);
	resultCommand = bufferCommand.pop();
	Asserts::AssertEqual("16) Type is finger all", resultCommand->type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("17) Action is contract", resultCommand->action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("18) Data is 10", resultCommand->data(), 10);
	Asserts::AssertTrue("19) Buffer empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("20) Buffer size 0", bufferCommand.size(), 0);
}

void BufferTest::PushPopRotatingTest() {
	cout << "Testing Push Pop Rotating" << endl;

	Buffer<char, 10> bufferChar;
	bufferChar.push('a');
	bufferChar.push('b');
	Asserts::AssertFalse("1) Buffer not empty", bufferChar.isEmpty());
	Asserts::AssertEqual("2) Buffer size 2", bufferChar.size(), 2);
	const char* resultChar = bufferChar.pop();
	Asserts::AssertEqual("3) Buffer pop equal 'a'", *resultChar, 'a');
	Asserts::AssertFalse("4) Buffer not empty", bufferChar.isEmpty());
	Asserts::AssertEqual("5) Buffer size 1", bufferChar.size(), 1);
	bufferChar.push('c');
	Asserts::AssertFalse("6) Buffer not empty", bufferChar.isEmpty());
	Asserts::AssertEqual("7) Buffer size 2", bufferChar.size(), 2);
	resultChar = bufferChar.pop();
	Asserts::AssertEqual("8) Buffer pop equal 'b'", *resultChar, 'b');
	Asserts::AssertFalse("9) Buffer empty", bufferChar.isEmpty());
	Asserts::AssertEqual("10) Buffer size 1", bufferChar.size(), 1);
	resultChar = bufferChar.pop();
	Asserts::AssertEqual("11) Buffer pop equal 'c'", *resultChar, 'c');
	Asserts::AssertTrue("12) Buffer empty", bufferChar.isEmpty());
	Asserts::AssertEqual("13) Buffer size 0", bufferChar.size(), 0);

	Command command1{ CommandTypeEnum::ADMIN, CommandActionEnum::SET_CHAR_BUFFER_CLEAR_TIMER, 10 };
	Command command2{ CommandTypeEnum::FINGER_ALL, CommandActionEnum::CONTRACT, 10 };
	Command command3{ CommandTypeEnum::FINGER_ALL, CommandActionEnum::STOP };
	Buffer<Command, 10> bufferCommand;
	bufferCommand.push(command1);
	bufferCommand.push(command2);
	Asserts::AssertFalse("14) Buffer not empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("15) Buffer size 2", bufferCommand.size(), 2);
	const Command* resultCommand = bufferCommand.pop();
	Asserts::AssertEqual("16) Type is admin", resultCommand->type(), CommandTypeEnum::ADMIN);
	Asserts::AssertEqual("17) Action is set char buffer timer", resultCommand->action(), CommandActionEnum::SET_CHAR_BUFFER_CLEAR_TIMER);
	Asserts::AssertEqual("18) Data is 10", resultCommand->data(), 10);
	Asserts::AssertFalse("19) Buffer not empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("20) Buffer size 1", bufferCommand.size(), 1);
	bufferCommand.push(command3);
	Asserts::AssertFalse("21) Buffer not empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("22) Buffer size 2", bufferCommand.size(), 2);
	resultCommand = bufferCommand.pop();
	Asserts::AssertEqual("23) Type is finger all", resultCommand->type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("24) Action is contract", resultCommand->action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("25) Data is 10", resultCommand->data(), 10);
	Asserts::AssertFalse("26) Buffer empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("27) Buffer size 0", bufferCommand.size(), 1);
	resultCommand = bufferCommand.pop();
	Asserts::AssertEqual("28) Type is finger all", resultCommand->type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("29) Action is stop", resultCommand->action(), CommandActionEnum::STOP);
	Asserts::AssertEqual("30) Data is 0", resultCommand->data(), 0);
	Asserts::AssertTrue("31) Buffer empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("32) Buffer size 0", bufferCommand.size(), 0);
}

void BufferTest::PushGetPeekTest() {
	cout << "Testing Push Get Peek" << endl;

	Buffer<char, 10> bufferChar;
	bufferChar.push('a');
	bufferChar.push('b');
	Asserts::AssertFalse("1) Buffer not empty", bufferChar.isEmpty());
	Asserts::AssertEqual("2) Buffer size 2", bufferChar.size(), 2);
	const char* resultChar = bufferChar.peek();
	Asserts::AssertEqual("3) Buffer peek equal 'a'", *resultChar, 'a');
	Asserts::AssertFalse("4) Buffer not empty", bufferChar.isEmpty());
	Asserts::AssertEqual("5) Buffer size 2", bufferChar.size(), 2);
	resultChar = bufferChar.get(1);
	Asserts::AssertEqual("6) Buffer get(1) equal 'b'", *resultChar, 'b');
	Asserts::AssertFalse("7) Buffer empty", bufferChar.isEmpty());
	Asserts::AssertEqual("8) Buffer size 2", bufferChar.size(), 2);
	resultChar = bufferChar.get(2);
	Asserts::AssertNull("9) Buffer get(2) is null", resultChar);

	Command command1{ CommandTypeEnum::ADMIN, CommandActionEnum::SET_CHAR_BUFFER_CLEAR_TIMER, 10 };
	Command command2{ CommandTypeEnum::FINGER_ALL, CommandActionEnum::CONTRACT, 10 };
	Buffer<Command, 10> bufferCommand;
	bufferCommand.push(command1);
	bufferCommand.push(command2);
	Asserts::AssertFalse("10) Buffer not empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("11) Buffer size 2", bufferCommand.size(), 2);
	const Command* resultCommand = bufferCommand.peek();
	Asserts::AssertEqual("12) Type is admin", resultCommand->type(), CommandTypeEnum::ADMIN);
	Asserts::AssertEqual("13) Action is set char buffer timer", resultCommand->action(), CommandActionEnum::SET_CHAR_BUFFER_CLEAR_TIMER);
	Asserts::AssertEqual("14) Data is 10", resultCommand->data(), 10);
	Asserts::AssertFalse("15) Buffer not empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("16) Buffer size 2", bufferCommand.size(), 2);
	resultCommand = bufferCommand.get(1);
	Asserts::AssertEqual("17) Type is finger all", resultCommand->type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("18) Action is contract", resultCommand->action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("19) Data is 10", resultCommand->data(), 10);
	Asserts::AssertFalse("20) Buffer empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("21) Buffer size 2", bufferCommand.size(), 2);
	resultCommand = bufferCommand.get(2);
	Asserts::AssertNull("22) Buffer get(2) is null", resultCommand);
}

void BufferTest::BufferOverflowTest() {
	cout << "Testing Buffer Overflow" << endl;

	Buffer<char, 2> bufferChar;
	bufferChar.push('a');
	bufferChar.push('b');
	Asserts::AssertFalse("1) Buffer not empty", bufferChar.isEmpty());
	Asserts::AssertEqual("2) Buffer size 2", bufferChar.size(), 2);
	bufferChar.push('c');
	Asserts::AssertEqual("3) Buffer size 2", bufferChar.size(), 2);
	const char* resultChar = bufferChar.peek();
	Asserts::AssertEqual("4) Buffer peek equal 'a'", *resultChar, 'a');
	resultChar = bufferChar.get(1);
	Asserts::AssertEqual("5) Buffer peek equal 'a'", *resultChar, 'b');

	Command command1{ CommandTypeEnum::ADMIN, CommandActionEnum::SET_CHAR_BUFFER_CLEAR_TIMER, 10 };
	Command command2{ CommandTypeEnum::FINGER_ALL, CommandActionEnum::CONTRACT, 10 };
	Command command3{ CommandTypeEnum::FINGER_ALL, CommandActionEnum::STOP };
	Buffer<Command, 2> bufferCommand;
	bufferCommand.push(command1);
	bufferCommand.push(command2);
	Asserts::AssertFalse("6) Buffer not empty", bufferCommand.isEmpty());
	Asserts::AssertEqual("7) Buffer size 2", bufferCommand.size(), 2);
	bufferCommand.push(command3);
	Asserts::AssertEqual("8) Buffer size 2", bufferCommand.size(), 2);
	const Command* resultCommand = bufferCommand.peek();
	Asserts::AssertEqual("9) Type is admin", resultCommand->type(), CommandTypeEnum::ADMIN);
	Asserts::AssertEqual("10) Action is set char buffer timer", resultCommand->action(), CommandActionEnum::SET_CHAR_BUFFER_CLEAR_TIMER);
	Asserts::AssertEqual("11) Data is 10", resultCommand->data(), 10);
	resultCommand = bufferCommand.get(1);
	Asserts::AssertEqual("12) Type is finger all", resultCommand->type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("13) Action is contract", resultCommand->action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("14) Data is 10", resultCommand->data(), 10);
}


#pragma once
#include <iostream>
#include <string>
#include "Asserts.h"
#include "../src/Command.h"
#include "../src/CommandController.h"

namespace CommandControllerTest {
	static void Run();
	static void ConstructorTest();
	static void AddCharsEmptyTest();
	static void AddCharsTimeoutTest();
	static void SetDefaultCommandTest();
	static void ValidCommandTest();
	static void ValidCommandTimeoutTest();
	static void SetCommandTimeoutTest();
	static void AdminCommandTimeoutTest();
	static void DifferentCommandTest();
	static void CommandPriorityTest();
}

void CommandControllerTest::Run() {
	CommandControllerTest::ConstructorTest();
	CommandControllerTest::AddCharsEmptyTest();
	CommandControllerTest::AddCharsTimeoutTest();
	CommandControllerTest::SetDefaultCommandTest();
	CommandControllerTest::ValidCommandTest();
	CommandControllerTest::ValidCommandTimeoutTest();
	CommandControllerTest::SetCommandTimeoutTest();
	CommandControllerTest::AdminCommandTimeoutTest();
	CommandControllerTest::DifferentCommandTest();
	CommandControllerTest::CommandPriorityTest();
}

void CommandControllerTest::ConstructorTest() {
	cout << "Constructor Test" << endl;
	CommandController commandController;
	unsigned long startTime = 1000;
	const Command* next = commandController.next(1000);
	Asserts::AssertEqual("1) Next command default", next->action(), CommandActionEnum::STOP);
}

void CommandControllerTest::AddCharsEmptyTest() {
	cout << "Add Chars Empty Test" << endl;
	CommandController commandController;
	unsigned long startTime = 1000;
	const char* chars = new char[0]{};
	commandController.addChars(startTime, chars, 0);
	const Command* next = commandController.next(startTime);
	Asserts::AssertEqual("1) Next command default", next->action(), CommandActionEnum::STOP);
	delete[] chars;
}

void CommandControllerTest::AddCharsTimeoutTest() {
	cout << "Add Chars Timeout Test" << endl;
	CommandController commandController;
	unsigned long startTime = 1000;

	const char* chars = new char[8]{COMMAND_START, 'F','A','C','O','N','T'};
	commandController.addChars(startTime, chars, 8);
	delete[] chars;
	chars = new char[1]{ COMMAND_END };
	commandController.addChars(startTime + 1000 + DEFAULT_CHAR_BUFFER_CLEAR_DURATION, chars, 1);
	delete[] chars;
	const Command* next = commandController.next(startTime + 1000 + DEFAULT_CHAR_BUFFER_CLEAR_DURATION);
	Asserts::AssertEqual("3) Next command default", next->action(), CommandActionEnum::STOP);
}

void CommandControllerTest::SetDefaultCommandTest() {
	cout << "Set Default Command Test" << endl;
	CommandController commandController;
	unsigned long startTime = 1000;

	Command command{ CommandTypeEnum::ADMIN, CommandActionEnum::CONTRACT, 10 };
	commandController.setDefaultCommand(command);

	const Command* next = commandController.next(startTime);
	Asserts::AssertEqual("1) Next command type admin", next->type(), CommandTypeEnum::ADMIN);
	Asserts::AssertEqual("2) Next command action contract", next->action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("3) Next command data 10", next->data(), 10);
}

void CommandControllerTest::ValidCommandTest() {
	cout << "Valid Command Test" << endl;
	CommandController commandController;
	unsigned long startTime = 1000;

	const char* chars = new char[11]{ COMMAND_START, 'F','A','C','O','N','T','1','0', COMMAND_END };
	commandController.addChars(startTime, chars, 11);
	delete[] chars;
	const Command* next = commandController.next(startTime);
	Asserts::AssertEqual("1) Next command type finger all", next->type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("2) Next command action contract", next->action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("3) Next command data 10", next->data(), 10);
	next = commandController.next(startTime + 1000 + DEFAULT_MOVEMENT_COMMAND_DURATION);
	Asserts::AssertEqual("4) Next command default", next->action(), CommandActionEnum::STOP);
}

void CommandControllerTest::ValidCommandTimeoutTest() {
	cout << "Valid Command Timeout Test" << endl;
	
	CommandController commandController;
	unsigned long startTime = 1000;

	const char* chars = new char[11]{ COMMAND_START, 'F','A','C','O','N','T','1','0', COMMAND_END };
	commandController.addChars(startTime, chars, 11);
	delete[] chars;
	chars = new char[11]{ COMMAND_START, 'F','A','C','O','N','T','2','2', COMMAND_END };
	commandController.addChars(startTime, chars, 11);
	delete[] chars;
	const Command* next = commandController.next(startTime);
	Asserts::AssertEqual("1) Next command type finger all", next->type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("2) Next command action contract", next->action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("3) Next command data 10", next->data(), 10);
	next = commandController.next(startTime);
	Asserts::AssertNull("4) Next command null", next);
	next = commandController.next(startTime + 1000 + DEFAULT_MOVEMENT_COMMAND_DURATION);
	Asserts::AssertEqual("5) Next command type finger all", next->type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("6) Next command action contract", next->action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("7) Next command data 22", next->data(), 22);
	next = commandController.next(startTime + 1000 + DEFAULT_MOVEMENT_COMMAND_DURATION);
	Asserts::AssertNull("8) Next command null", next);
	next = commandController.next(startTime + 2*(1000 + DEFAULT_MOVEMENT_COMMAND_DURATION));
	Asserts::AssertEqual("9) Next command default", next->action(), CommandActionEnum::STOP);
}

void CommandControllerTest::SetCommandTimeoutTest() {
	cout << "Set Command Timeout Test" << endl;

	CommandController commandController;
	unsigned long startTime = 1000;
	commandController.setMovementCommandDuration(100);

	const char* chars = new char[22]{ COMMAND_START, 'F','A','E','X','T','D','2','2', COMMAND_END, COMMAND_START, 'F','A','E','X','T','D','1','0', COMMAND_END };
	commandController.addChars(startTime, chars, 22);
	delete[] chars;
	const Command* next = commandController.next(startTime);
	Asserts::AssertEqual("1) Next command type finger all", next->type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("2) Next command action extend", next->action(), CommandActionEnum::EXTEND);
	Asserts::AssertEqual("3) Next command data 22", next->data(), 22);
	next = commandController.next(startTime);
	Asserts::AssertNull("4) Next command null", next);
	next = commandController.next(startTime + 101);
	Asserts::AssertEqual("5) Next command type finger all", next->type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("6) Next command action extend", next->action(), CommandActionEnum::EXTEND);
	Asserts::AssertEqual("7) Next command data 10", next->data(), 10);
}

void CommandControllerTest::AdminCommandTimeoutTest() {
	cout << "Admin Command Timeout Test" << endl;

	CommandController commandController;
	unsigned long startTime = 1000;

	const char* chars = new char[22]{ COMMAND_START, 'A','D','C','O','N','T','1','0', COMMAND_END, COMMAND_START, 'A','D','C','O','N','T','1','0', COMMAND_END };
	commandController.addChars(startTime, chars, 22);
	delete[] chars;
	const Command* next = commandController.next(startTime);
	Asserts::AssertEqual("1) Next command type admin", next->type(), CommandTypeEnum::ADMIN);
	Asserts::AssertEqual("2) Next command action contract", next->action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("3) Next command data 10", next->data(), 10);
	next = commandController.next(startTime);
	Asserts::AssertEqual("4) Next command type admin", next->type(), CommandTypeEnum::ADMIN);
	Asserts::AssertEqual("5) Next command action contract", next->action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("6) Next command data 10", next->data(), 10);
}

void CommandControllerTest::DifferentCommandTest() {
	cout << "Different Command Test" << endl;
	CommandController commandController;
	unsigned long startTime = 1000;

	const char* chars = new char[22]{ COMMAND_START, 'F','A','C','O','N','T','1','0', COMMAND_END, COMMAND_START, 'F','A','E','X','T','D','2','2', COMMAND_END };
	commandController.addChars(startTime, chars, 22);
	delete[] chars;
	const Command* next = commandController.next(startTime);
	Asserts::AssertEqual("1) Next command type finger all", next->type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("2) Next command action extend", next->action(), CommandActionEnum::EXTEND);
	Asserts::AssertEqual("3) Next command data 22", next->data(), 22);
}

void CommandControllerTest::CommandPriorityTest() {
	cout << "Command Priority Test" << endl;
	CommandController commandController;
	unsigned long startTime = 1000;

	const char* chars = new char[22]{ COMMAND_START, 'F','A','E','X','T','D','2','2', COMMAND_END, COMMAND_START, 'A','D','C','O','N','T','1','0', COMMAND_END };
	commandController.addChars(startTime, chars, 22);
	delete[] chars;
	const Command* next = commandController.next(startTime);
	Asserts::AssertEqual("1) Next command type admin", next->type(), CommandTypeEnum::ADMIN);
	Asserts::AssertEqual("2) Next command action contract", next->action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("3) Next command data 10", next->data(), 10);
	next = commandController.next(startTime);
	Asserts::AssertEqual("4) Next command type finger all", next->type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("5) Next command action extend", next->action(), CommandActionEnum::EXTEND);
	Asserts::AssertEqual("6) Next command data 22", next->data(), 22);
}
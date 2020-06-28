#pragma once
#include <iostream>
#include <string>
#include "Asserts.h"
#include "../src/CommandConfig.h"
#include "../src/Command.h"

namespace CommandTest {
	static void Run();
	static void ConstructorTest();
	static void OperatorTest();
	static void TryParseTest();
}

void CommandTest::Run() {
	CommandTest::ConstructorTest();
	CommandTest::OperatorTest();
	CommandTest::TryParseTest();
}

void CommandTest::ConstructorTest() {
	cout << "Constructor Test" << endl;
	Command empty;
	Asserts::AssertEqual("1) Type is undefined", empty.type(), CommandTypeEnum::UNDEFINED);
	Asserts::AssertEqual("2) Action is undefined", empty.action(), CommandActionEnum::UNDEFINED);
	Asserts::AssertEqual("3) Data is 0", empty.data(), 0);

	Command command{ CommandTypeEnum::FINGER_ALL, CommandActionEnum::CONTRACT, 20 };
	Asserts::AssertEqual("4) Type is finger all", command.type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("5) Action is contract", command.action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("6) Data is 20", command.data(), 20);

	Command copy(command);
	Asserts::AssertEqual("7) Type is finger all", copy.type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("8) Action is contract", copy.action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("9) Data is 20", copy.data(), 20);

	Command nodata{ CommandTypeEnum::FINGER_ALL, CommandActionEnum::STOP };
	Asserts::AssertEqual("10) Type is finger all", nodata.type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("11) Action is contract", nodata.action(), CommandActionEnum::STOP);
	Asserts::AssertEqual("12) Data is 20", nodata.data(), 0);
}

void CommandTest::OperatorTest() {
	cout << "Operator Test" << endl;

	Command command1{ CommandTypeEnum::FINGER_ALL, CommandActionEnum::CONTRACT, 20 };
	Command command2{ CommandTypeEnum::FINGER_ALL, CommandActionEnum::CONTRACT, 20 };
	Command command3{ CommandTypeEnum::ADMIN, CommandActionEnum::EXTEND, 10 };

	Asserts::AssertTrue("1) Equality operator", command1 == command2);
	Asserts::AssertFalse("2) Equality operator", command1 == command3);
	Asserts::AssertTrue("3) Inequality operator", command1 != command3);
	Asserts::AssertFalse("4) Inequality operator", command1 != command2);

	Command command4 = command1;
	Asserts::AssertEqual("5) Assignment operator type", command4.type(), command1.type());
	Asserts::AssertEqual("6) Assignment operator action", command4.action(), command1.action());
	Asserts::AssertEqual("7) Assignment operator data", command4.data(), command1.data());

	command4 = command3;
	Asserts::AssertNotEqual("8) Ressignment type", command4.type(), command1.type());
	Asserts::AssertNotEqual("9) Ressignment action", command4.action(), command1.action());
	Asserts::AssertNotEqual("10) Ressignment data", command4.data(), command1.data());
}

void CommandTest::TryParseTest() {
	cout << "Try Parse Test" << endl;

	char chars[MAX_CHARACTERS_IN_BUFFER];
	Command command;
	bool parsed = command.tryParse(chars, 0);
	Asserts::AssertFalse("1) Parsed false", parsed);

	chars[0] = 'F';
	chars[1] = 'G';
	parsed = command.tryParse(chars, 2);
	Asserts::AssertFalse("2) Parsed false", parsed);

	chars[0] = COMMAND_START;
	chars[1] = COMMAND_END;
	parsed = command.tryParse(chars, 2);
	Asserts::AssertFalse("3) Parsed false", parsed);

	chars[0] = COMMAND_START;
	chars[1] = 'F';
	chars[2] = 'G';
	chars[3] = COMMAND_END;
	parsed = command.tryParse(chars, 4);
	Asserts::AssertFalse("4) Parsed false", parsed);

	chars[0] = COMMAND_START;
	chars[1] = 'F';
	chars[2] = 'A';
	chars[3] = COMMAND_END;
	parsed = command.tryParse(chars, 4);
	Asserts::AssertFalse("5) Parsed false", parsed);

	chars[0] = COMMAND_START;
	chars[1] = 'F';
	chars[2] = 'A';
	chars[3] = 'S';
	chars[4] = 'T';
	chars[5] = 'O';
	chars[6] = 'P';
	chars[7] = COMMAND_END;
	parsed = command.tryParse(chars, 8);
	Asserts::AssertTrue("6) Parsed true", parsed);
	Asserts::AssertEqual("7) Type is finger all", command.type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("8) Action is stop", command.action(), CommandActionEnum::STOP);
	Asserts::AssertEqual("9) Data is 0", command.data(), 0);

	chars[0] = COMMAND_START;
	chars[1] = 'F';
	chars[2] = 'A';
	chars[3] = 'C';
	chars[4] = 'O';
	chars[5] = 'N';
	chars[6] = 'T';
	chars[7] = '1';
	chars[8] = '0';
	chars[9] = COMMAND_END;
	parsed = command.tryParse(chars, 10);
	Asserts::AssertTrue("10) Parsed true", parsed);
	Asserts::AssertEqual("11) Type is finger all", command.type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("12) Action is contract", command.action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("13) Data is 10", command.data(), 10);

	chars[0] = COMMAND_START;
	chars[1] = 'F';
	chars[2] = 'A';
	chars[3] = 'C';
	chars[4] = 'O';
	chars[5] = 'N';
	chars[6] = 'T';
	chars[7] = '-';
	chars[8] = '1';
	chars[9] = '0';
	chars[10] = COMMAND_END;
	parsed = command.tryParse(chars, 11);
	Asserts::AssertTrue("14) Parsed true", parsed);
	Asserts::AssertEqual("15) Type is finger all", command.type(), CommandTypeEnum::FINGER_ALL);
	Asserts::AssertEqual("16) Action is contract", command.action(), CommandActionEnum::CONTRACT);
	Asserts::AssertEqual("17) Data is -10", command.data(), -10);

	chars[0] = COMMAND_START;
	chars[1] = 'F';
	chars[2] = 'A';
	chars[3] = 'S';
	chars[4] = 'T';
	chars[5] = 'O';
	chars[6] = 'P';
	chars[7] = '-';
	chars[8] = 'a';
	chars[9] = '0';
	chars[10] = COMMAND_END;
	parsed = command.tryParse(chars, 11);
	Asserts::AssertFalse("18) Parsed false", parsed);

	chars[0] = COMMAND_START;
	chars[1] = 'F';
	chars[2] = 'A';
	chars[3] = 'S';
	chars[4] = 'T';
	chars[5] = 'O';
	chars[6] = 'P';
	chars[7] = '-';
	chars[8] = 'a';
	chars[9] = '0';
	chars[10] = COMMAND_END;
	chars[11] = COMMAND_START;
	chars[12] = 'F';
	chars[13] = 'A';
	chars[14] = 'S';
	chars[15] = 'T';
	chars[16] = 'O';
	chars[17] = 'P';
	chars[18] = '-';
	chars[19] = 'a';
	chars[20] = '0';
	chars[21] = COMMAND_END;
	parsed = command.tryParse(chars, 22);
	Asserts::AssertFalse("19) Parsed false", parsed);
}
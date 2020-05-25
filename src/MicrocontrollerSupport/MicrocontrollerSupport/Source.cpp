#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "ElasticBuffer.h"
#include "Timer.h"
#include "Command.h"
#include <iostream>
#include "CommandDecoder.h"
#include "CommandSelector.h"

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif

using namespace std;

void testCommandDecoder() {
	cout << "Testing Command Decoder" << endl;

	CommandDecoder* commandDecoder = new CommandDecoder();
	const Command* contract0 = new Command(CommandType::FINGER_ALL, CommandAction::CONTRACT, 0);
	const Command* contract12 = new Command(CommandType::FINGER_ALL, CommandAction::CONTRACT, -12);

	char* c1 = nullptr;
	char* c2 = new char[0];
	char* c3 = new char[1]{ 'a' };
	char* c4 = new char[1]{ '#' };
	char* c5 = new char[8]{ '#', 'F', 'A', 'C', 'O', 'N', 'T', '\n' };
	char* c6 = new char[16]{ '#', 'F', 'A', 'C', 'O', 'N', 'T', '\n', '#', 'F', 'A', 'C', 'O', 'N', 'T', '\n' };
	char* c7 = new char[14]{ '#', 'F', 'A', 'C', 'O', 'N', 'T', '\n', '#', 'F', 'A', 'C', 'O', 'N' };
	char* c8 = new char[11]{ '#', 'F', 'A', 'C', 'O', 'N', 'T', '-', '1', '2', '\n' };
	char* c9 = new char[11]{ '#', 'F', 'A', 'C', 'O', 'N', 'T', '-', '1', 'a', '\n' };
	char* c10 = new char[6]{ '#', 'F', 'A', 'C', 'O', '\n' };
	char* c11 = new char[11]{ '#', 'F', 'A', 'C', 'O', 'D', 'D', '-', '1', '2', '\n' };
	char* c12 = new char[14]{ '#', 'F', 'A', 'C', 'O', 'N', 'T', '\n', '#', 'F', 'A', 'C', 'O', '\n' };
	char* c13 = new char[4]{ '#', 'C', 'O', '\n' };

	commandDecoder->addChars(c1, 0);
	if (commandDecoder->hasNext() || commandDecoder->next() != nullptr) {
		cout << "Test 1 failed" << endl;
	}

	commandDecoder->addChars(c2, 0);
	if (commandDecoder->hasNext() || commandDecoder->next() != nullptr) {
		cout << "Test 2 failed" << endl;
	}

	commandDecoder->addChars(c3, 1);
	if (commandDecoder->hasNext() || commandDecoder->next() != nullptr) {
		cout << "Test 3 failed" << endl;
	}

	commandDecoder->addChars(c4, 1);
	if (commandDecoder->hasNext() || commandDecoder->next() != nullptr) {
		cout << "Test 4 failed" << endl;
	}

	commandDecoder->clear();

	commandDecoder->addChars(c5, 8);
	if (commandDecoder->hasNext()) {
		const Command* command = commandDecoder->next();
		if (*command != *contract0) {
			cout << "Test 5 failed" << endl;
		}
		delete command;
	}
	else {
		cout << "Test 5 failed" << endl;
	}
	commandDecoder->clear();

	commandDecoder->addChars(c6, 16);
	if (commandDecoder->hasNext()) {
		const Command* command = commandDecoder->next();
		if (*command != *contract0) {
			cout << "Test 6 failed" << endl;
		}
		delete command;

		if (commandDecoder->hasNext()) {
			command = commandDecoder->next();
			if (*command != *contract0) {
				cout << "Test 6 failed" << endl;
			}
			delete command;
		}
		else {
			cout << "Test 6 failed" << endl;
		}
	}
	else {
		cout << "Test 6 failed" << endl;
	}
	commandDecoder->clear();

	commandDecoder->addChars(c7, 14);
	if (commandDecoder->hasNext()) {
		const Command* command = commandDecoder->next();
		if (*command != *contract0) {
			cout << "Test 7 failed" << endl;
		}
		delete command;

		if (commandDecoder->hasNext()) {
			cout << "Test 7 failed" << endl;
		}
	}
	else {
		cout << "Test 7 failed" << endl;
	}
	commandDecoder->clear();

	commandDecoder->addChars(c8, 11);
	if (commandDecoder->hasNext()) {
		const Command* command = commandDecoder->next();
		if (*command != *contract12) {
			cout << "Test 8 failed" << endl;
		}
		delete command;
	}
	else {
		cout << "Test 8 failed" << endl;
	}
	commandDecoder->clear();

	commandDecoder->addChars(c9, 11);
	if (commandDecoder->hasNext()) {
		const Command* command = commandDecoder->next();
		if (command->type() != CommandType::FINGER_ALL && command->action() == CommandAction::CONTRACT && command->bLength() != 3) {
			cout << "Test 9 failed" << endl;
		}
		delete command;
	}
	else {
		cout << "Test 9 failed" << endl;
	}
	commandDecoder->clear();

	commandDecoder->addChars(c10, 6);
	if (commandDecoder->hasNext()) {
		const Command* command = commandDecoder->next();
		if (command->type() != CommandType::FINGER_ALL && command->action() != CommandAction::UNDEFINED && command->bLength() != 2) {
			cout << "Test 10 failed" << endl;
		}
		delete command;
	}
	else {
		cout << "Test 10 failed" << endl;
	}
	commandDecoder->clear();

	commandDecoder->addChars(c11, 11);
	if (commandDecoder->hasNext()) {
		const Command* command = commandDecoder->next();
		if (command->type() != CommandType::FINGER_ALL && command->action() != CommandAction::UNDEFINED && command->bLength() != 7) {
			cout << "Test 11 failed" << endl;
		}
		delete command;
	}
	else {
		cout << "Test 11 failed" << endl;
	}

	commandDecoder->addChars(c12, 14);
	if (commandDecoder->hasNext()) {
		const Command* command = commandDecoder->next();
		if (*command != *contract0) {
			cout << "Test 12 failed" << endl;
		}
		delete command;
	}
	else {
		cout << "Test 12 failed" << endl;
	}
	if (commandDecoder->hasNext()) {
		const Command* command = commandDecoder->next();
		if (command->type() != CommandType::FINGER_ALL && command->action() != CommandAction::UNDEFINED && command->bLength() != 2) {
			cout << "Test 12 failed" << endl;
		}
		delete command;
	}
	else {
		cout << "Test 12 failed" << endl;
	}
	commandDecoder->clear();

	commandDecoder->addChars(c13, 4);
	if (commandDecoder->hasNext()) {
		const Command* command = commandDecoder->next();
		if (command->type() != CommandType::UNDEFINED && command->action() != CommandAction::UNDEFINED && command->bLength() != 4) {
			cout << "Test 13 failed" << endl;
		}
		delete command;
	}
	else {
		cout << "Test 13 failed" << endl;
	}

	delete[] c2;
	delete[] c3;
	delete[] c4;
	delete[] c5;
	delete[] c6;
	delete[] c7;
	delete[] c8;
	delete[] c9;
	delete[] c10;
	delete[] c11;
	delete[] c12;
	delete[] c13;
	delete contract0;
	delete contract12;
	delete commandDecoder;
	cout << "All Tests Done" << endl << endl;
}

void testCommand() {
	cout << "Testing Command" << endl;

	Command* command = new Command();
	Command* contract0 = new Command(CommandType::FINGER_ALL, CommandAction::CONTRACT, 0);

	if (command->type() != CommandType::UNDEFINED || command->action() != CommandAction::UNDEFINED || command->nData() != 0 || command->bLength() != 0 || command->bData() != nullptr) {
		cout << "command undef init failed" << endl;
	}

	if (contract0->type() != CommandType::FINGER_ALL || contract0->action() != CommandAction::CONTRACT || contract0->nData() != 0 || command->bLength() != 0 || contract0->bData() != nullptr) {
		cout << "command contract init failed" << endl;
	}

	Command* contract12 = new Command(CommandType::FINGER_ALL, CommandAction::CONTRACT, -12, new char[2]{'a', 'b'}, 2);
	*contract0 = *contract12;
	delete contract12;

	if (contract0->type() != CommandType::FINGER_ALL || contract0->action() != CommandAction::CONTRACT || contract0->nData() != -12 || contract0->bLength() != 2 || contract0->bData()[0] != 'a' || contract0->bData()[1] != 'b') {
		cout << "command contract copy failed" << endl;
	}

	delete command;
	delete contract0;

	cout << "All Tests Done" << endl << endl;
}

void testEBuffer() {
	cout << "Testing Elastic Buffer" << endl;

	// Test memory leaks
	const Command* command = new Command(CommandType::ADMIN, CommandAction::LIST_BUFFER);
	Buffer<Command>* buffer = new ElasticBuffer<Command>();
	buffer->push(*command);
	delete command;
	delete buffer;

	Buffer<int> *q = new ElasticBuffer<int>();
	auto& ElasticBuffer = *q;

	int i = 6;
	int j = 1;
	int k = 5;

	ElasticBuffer.push(i);
	ElasticBuffer.push(j);
	ElasticBuffer.push(k);
	ElasticBuffer.push(i);

	for (int index = 0; index < ElasticBuffer.size(); ++index) {
		if (ElasticBuffer.get(index) == nullptr) {
			cout << "Get index failed." << endl;
		}
	}

	const int* c = ElasticBuffer.pop();
	if (*c != i) {
		cout << "Pop failed." << endl;
	}
	delete c;

	const int* d = ElasticBuffer.remove(2);
	if (*d != i) {
		cout << "Remove failed." << endl;
	}
	delete d;

	const int* e = ElasticBuffer.get(1);
	if (*e != k) {
		cout << "Get failed." << endl;
	}

	delete q;

	cout << "All Tests Done" << endl << endl;
}

void testTimer() {
	cout << "Testing Timer" << endl;

	const unsigned long startTime = 100000;
	const int duration = 4000;
	Timer* timer = new Timer(startTime, duration);

	const unsigned long currentTime1 = 102000;
	if (timer->isElapsed(currentTime1)) {
		cout << "isElapsed failed before." << endl;
	}

	const unsigned long currentTime2 = 104000;
	if (timer->isElapsed(currentTime2)) {
		cout << "isElapsed failed during." << endl;
	}

	const unsigned long currentTime3 = 104001;
	if (!timer->isElapsed(currentTime3)) {
		cout << "isElapsed failed after." << endl;
	}

	delete timer;
	cout << "All Tests Done" << endl << endl;
}

void testCommandSelector() {
	cout << "Testing Command Selector" << endl;
	CommandSelector* selector = new CommandSelector();

	const Command* print = new Command(CommandType::ADMIN, CommandAction::LIST_BUFFER);
	const Command* contract0 = new Command(CommandType::FINGER_ALL, CommandAction::CONTRACT);
	const Command* contract12 = new Command(CommandType::FINGER_ALL, CommandAction::CONTRACT, -12);

	selector->add(*print);
	selector->add(*contract0);
	selector->add(*contract12);

	if (selector->hasNext(CommandType::UNDEFINED) || !selector->hasNext(CommandType::ADMIN) || !selector->hasNext(CommandType::FINGER_ALL)) {
		cout << "hasNext failed." << endl;
	}

	const Command* next = selector->next(CommandType::UNDEFINED);
	if (next != nullptr) {
		cout << "next undef failed." << endl;
	}
	delete next;

	next = selector->next(CommandType::ADMIN);
	if (next == nullptr || *next != *print) {
		cout << "next undef failed." << endl;
	}
	delete next;

	next = selector->next(CommandType::FINGER_ALL);
	if (next == nullptr || *next != *contract0) {
		cout << "next fingerall1 failed." << endl;
	}
	delete next;

	next = selector->next(CommandType::FINGER_ALL);
	if (next == nullptr || *next != *contract12) {
		cout << "next fingerall2 failed." << endl;
	}
	delete next;

	delete print;
	delete contract0;
	delete contract12;
	delete selector;

	cout << "All Tests Done" << endl << endl;
}

int main(int argc, char* argv[]) {
	testTimer();
	testCommand();
	testEBuffer();
	testCommandDecoder();
	testCommandSelector();

	_CrtDumpMemoryLeaks();

	return 0;
}

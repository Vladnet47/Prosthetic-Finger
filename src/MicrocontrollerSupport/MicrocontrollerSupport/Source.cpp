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

void testEBuffer() {
	cout << "Testing Elastic Buffer" << endl;

	ElasticBuffer<int> *q = new ElasticBuffer<int>();
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

/*
void testCommandSelector() {
	cout << "Testing Command Selector" << endl;
	CommandSelector* selector = new CommandSelector();

	const Command* undefined = new Command(UNDEFINED, 0);
	const Command* print = new Command(LIST_BUFFER);
	const Command* contract0 = new Command(CONTRACT, 0);
	const Command* contract12 = new Command(CONTRACT, -12);


	cout << "All Tests Done" << endl << endl;
}
*/

int main(int argc, char* argv[]) {
	testEBuffer();
	testTimer();
	testCommandDecoder();

	_CrtDumpMemoryLeaks();

	return 0;
}

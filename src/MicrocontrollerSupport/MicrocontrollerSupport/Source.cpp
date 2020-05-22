#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif

#include "Queue.h"
#include "Command.h"
#include <iostream>
#include "CommandInterpreter.h"

using namespace std;

const int QUEUE_SIZE = 3;

//template <class T>
//void printQueue(Queue<T>& queue) {
//	const int size = queue.size();
//
//	if (size > 0) {
//		T* list = queue.list();
//		for (int i = 0; i < size; ++i) {
//			cout << "[" << list[i] << "]";
//		}
//
//		delete[] list;
//	}
//
//	const int emptySlots = QUEUE_SIZE - size;
//	for (int i = 0; i < emptySlots; ++i) {
//		cout << "[]";
//	}
//
//	cout << endl;
//}

void testInterpreter() {
	const CommandInterpreter* commandInterpreter = new CommandInterpreter();
	const Command* contract0 = new Command(CONTRACT_HAND, 0);
	const Command* contract12 = new Command(CONTRACT_HAND, -12);

	char* c1 = nullptr;
	char* c2 = new char[0];
	char* c3 = new char[1]{ 'a' };
	char* c4 = new char[1]{ '#' };
	char* c5 = new char[6]{ '#', 'C', 'O', 'N', 'T', '\n' };
	char* c6 = new char[12]{ '#', 'C', 'O', 'N', 'T', '\n', '#', 'C', 'O', 'N', 'T', '\n' };
	char* c7 = new char[10]{ '#', 'C', 'O', 'N', 'T', '\n', '#', 'C', 'O', 'N' };
	char* c8 = new char[9]{ '#', 'C', 'O', 'N', 'T', '-', '1', '2', '\n' };
	char* c9 = new char[9]{ '#', 'C', 'O', 'N', 'T', '-', '1', 'a', '\n' };
	char* c10 = new char[4]{ '#', 'C', 'O', '\n' };
	char* c11 = new char[9]{ '#', 'C', 'O', 'D', 'D', '-', '1', '2', '\n' };
	char* c12 = new char[10]{ '#', 'C', 'O', 'N', 'T', '\n', '#', 'C', 'O', '\n' };

	Command* commands = nullptr;
	int count = commandInterpreter->parseCommands(commands, c1, 0);
	if (count != 0) {
		cout << "Test 1 failed." << endl;
	}
	delete commands;

	commands = nullptr;
	count = commandInterpreter->parseCommands(commands, c2, 0);
	if (count != 0) {
		cout << "Test 2 failed." << endl;
	}
	delete commands;

	commands = nullptr;
	count = commandInterpreter->parseCommands(commands, c3, 1);
	if (count != 0) {
		cout << "Test 3 failed." << endl;
	}
	delete commands;

	commands = nullptr;
	count = commandInterpreter->parseCommands(commands, c4, 1);
	if (count != 0) {
		cout << "Test 4 failed." << endl;
	}
	delete commands;

	commands = nullptr;
	count = commandInterpreter->parseCommands(commands, c5, 6);
	if (count != 1 || commands[0] != *contract0) {
		cout << "Test 5 failed." << endl;
	}
	delete[] commands;

	commands = nullptr;
	count = commandInterpreter->parseCommands(commands, c6, 12);
	if (count != 2 || commands[0] != *contract0 || commands[1] != *contract0) {
		cout << "Test 6 failed." << endl;
	}
	delete[] commands;

	commands = nullptr;
	count = commandInterpreter->parseCommands(commands, c7, 10);
	if (count != 1 || commands[0] != *contract0) {
		cout << "Test 7 failed." << endl;
	}
	delete[] commands;

	
	commands = nullptr;
	count = commandInterpreter->parseCommands(commands, c8, 9);
	if (count != 1 || commands[0] != *contract12) {
		cout << "Test 8 failed." << endl;
	}
	delete[] commands;

	commands = nullptr;
	count = commandInterpreter->parseCommands(commands, c9, 9);
	if (count != 1 || commands[0].type() != CONTRACT_HAND || commands[0].bLength() != 3) {
		cout << "Test 9 failed." << endl;
	}
	delete[] commands;

	commands = nullptr;
	count = commandInterpreter->parseCommands(commands, c10, 4);
	if (count != 1 || commands[0].type() != UNDEFINED || commands[0].bLength() != 2) {
		cout << "Test 10 failed." << endl;
	}
	delete[] commands;

	commands = nullptr;
	count = commandInterpreter->parseCommands(commands, c11, 9);
	if (count != 1 || commands[0].type() != UNDEFINED || commands[0].bLength() != 7) {
		cout << "Test 11 failed." << endl;
	}
	delete[] commands;

	commands = nullptr;
	count = commandInterpreter->parseCommands(commands, c12, 10);
	if (count != 2 || commands[0] != *contract0 || commands[1].type() != UNDEFINED || commands[1].bLength() != 2) {
		Command someCommand = commands[1];
		cout << "Test 12 failed." << endl;
	}
	delete[] commands;

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
	delete contract0;
	delete contract12;
	delete commandInterpreter;

	cout << "All Interpreter tests passed." << endl;
}

void testIntQueue() {
	Queue<int> *q = new Queue<int>(QUEUE_SIZE);
	auto& queue = *q;

	int i = 6;
	int j = 1;
	int k = 5;

	//printQueue(queue);

	queue.push(i);
	//printQueue(queue);

	queue.push(j);
	queue.push(k);
	//printQueue(queue);

	queue.push(i);
	//printQueue(queue);

	const int* c = queue.popFront();
	if (*c != j) {
		cout << "Pop front failed." << endl;
	}
	//printQueue(queue);

	const int* d = queue.popBack();
	if (*d != i) {
		cout << "Pop back failed." << endl;
	}
	//printQueue(queue);

	const int* e = queue.get(0);
	if (*e != k) {
		cout << "Get failed." << endl;
	}
	//printQueue(queue);

	delete q;
}

int main(int argc, char* argv[]) {
	testInterpreter();

	_CrtDumpMemoryLeaks();

	return 0;
}

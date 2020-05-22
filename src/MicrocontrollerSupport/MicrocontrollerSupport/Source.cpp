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
	CommandInterpreter* interpreter = new CommandInterpreter();

	const Command* undefined = new Command();
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
	char* c11 = new char[10]{ '#', 'C', 'O', 'N', 'T', '\n', '#', 'C', 'O', '\n' };

	const int co1 = interpreter->countCommands(c1, 0);
	if (co1 != 0) {
		cout << "Failed at co1" << endl;
		return;
	}
	const Command* cm1 = interpreter->parseCommands(c1, 0, co1);

	const int co2 = interpreter->countCommands(c2, 0);
	if (co2 != 0) {
		cout << "Failed at co2" << endl;
		return;
	}
	const Command* cm2 = interpreter->parseCommands(c2, 0, co2);

	const int co3 = interpreter->countCommands(c3, 1);
	if (co3 != 0) {
		cout << "Failed at co3" << endl;
		return;
	}
	const Command* cm3 = interpreter->parseCommands(c3, 1, co3);

	const int co4 = interpreter->countCommands(c4, 1);
	if (co4 != 0) {
		cout << "Failed at co4" << endl;
		return;
	}
	const Command* cm4 = interpreter->parseCommands(c4, 1, co4);

	const int co5 = interpreter->countCommands(c5, 6);
	if (co5 != 1) {
		cout << "Failed at co5" << endl;
		return;
	}
	const Command* cm5 = interpreter->parseCommands(c5, 6, co5);
	if (cm5[0] != *contract0) {
		cout << "Failed at cm5" << endl;
		return;
	}

	const int co6 = interpreter->countCommands(c6, 12);
	if (co6 != 2) {
		cout << "Failed at co6" << endl;
		return;
	}
	const Command* cm6 = interpreter->parseCommands(c6, 12, co6);
	if (cm6[0] != *contract0 && cm6[1] != *contract0) {
		cout << "Failed at cm6" << endl;
		return;
	}

	const int co7 = interpreter->countCommands(c7, 10);
	if (co7 != 1) {
		cout << "Failed at co7" << endl;
		return;
	}
	const Command* cm7 = interpreter->parseCommands(c7, 10, co7);
	if (cm7[0] != *contract0 && cm7[1] != *undefined) {
		cout << "Failed at cm7" << endl;
		return;
	}

	const int co8 = interpreter->countCommands(c8, 9);
	if (co8 != 1) {
		cout << "Failed at co8" << endl;
		return;
	}
	const Command* cm8 = interpreter->parseCommands(c8, 9, co8);
	if (cm8[0] != *contract12) {
		cout << "Failed at cm8" << endl;
		return;
	}

	const int co9 = interpreter->countCommands(c9, 9);
	if (co9 != 1) {
		cout << "Failed at co9" << endl;
		return;
	}
	const Command* cm9 = interpreter->parseCommands(c9, 9, co9);
	if (cm9[0] != *contract0) {
		cout << "Failed at cm9" << endl;
		return;
	}

	const int co10 = interpreter->countCommands(c10, 4);
	if (co10 != 1) {
		cout << "Failed at co10" << endl;
		return;
	}
	const Command* cm10 = interpreter->parseCommands(c10, 14, co10);
	if (cm10[0] != *undefined) {
		cout << "Failed at cm10" << endl;
		return;
	}

	const int co11 = interpreter->countCommands(c11, 10);
	if (co11 != 2) {
		cout << "Failed at co11" << endl;
		return;
	}
	const Command* cm11 = interpreter->parseCommands(c11, 11, co11);
	if (cm11[0] != *contract0 && cm11[1] != *undefined) {
		cout << "Failed at cm11" << endl;
		return;
	}

	delete c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11;
	delete[] cm1, cm2, cm3, cm4, cm5, cm6, cm7, cm8, cm9, cm10, cm11;
	delete interpreter;
	delete undefined, contract0, contract12;

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

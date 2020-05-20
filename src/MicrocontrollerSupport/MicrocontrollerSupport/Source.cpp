#include "Queue.h"
#include "Command.h"
#include <iostream>

using namespace std;

const int QUEUE_SIZE = 3;

template <class T>
void printQueue(Queue<T>& queue) {
	const int size = queue.size();

	if (size > 0) {
		T* list = queue.list();
		for (int i = 0; i < size; ++i) {
			cout << "[" << list[i] << "]";
		}
	}

	const int emptySlots = QUEUE_SIZE - size;
	for (int i = 0; i < emptySlots; ++i) {
		cout << "[]";
	}

	cout << endl;
}

int main(int argc, char* argv[]) {
	Queue<int> queue(QUEUE_SIZE);

	int* i = new int(1);
	int* j = new int(2);
	int* k = new int(3);

	printQueue(queue);

	queue.push(i);
	printQueue(queue);

	queue.push(j);
	queue.push(k);
	printQueue(queue);

	queue.push(i);
	printQueue(queue);

	int* c = queue.popFront();
	if (*c != *j) {
		cout << "Pop front failed." << endl;
	}
	printQueue(queue);

	int* d = queue.popBack();
	if (*d != *i) {
		cout << "Pop back failed." << endl;
	}
	printQueue(queue);

	int* e = queue.get(0);
	if (*e != *k) {
		cout << "Get failed." << endl;
	}
	printQueue(queue);

	return 0;
}

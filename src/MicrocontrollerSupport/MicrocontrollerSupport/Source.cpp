#include "CommandBuffer.h"
#include <iostream>

using namespace std;


bool testQueueCB() {
	CommandBuffer* buffer = new CommandBuffer(3);
	if (buffer == nullptr) {
		cout << "ERROR: Failed to construct buffer." << endl;
		return false;
	}

	if (buffer->size() != 0 || !buffer->isEmpty()) {
		cout << "ERROR: Incorrect buffer size." << endl;
		return false;
	}

	buffer->push(CONTRACT_HAND, 2);
	buffer->push(EXTEND_HAND);
	buffer->push(15);

	if (buffer->size() != 3 || buffer->isEmpty()) {
		cout << "ERROR: Incorrect buffer size." << endl;
		return false;
	}

	Command* next = buffer->peek();
	if (next->type != CONTRACT_HAND || next->data != 2 || buffer->size() != 3) {
		cout << "ERROR: Peek function fails." << endl;
		return false;
	}
	delete next;

	next = buffer->pop();
	if (next->type != CONTRACT_HAND || next->data != 2 || buffer->size() != 2) {
		cout << "ERROR: Pop function fails." << endl;
		return false;
	}
	delete next;

	next = buffer->pop();
	if (next->type != EXTEND_HAND || next->data != 0 || buffer->size() != 1) {
		cout << "ERROR: Pop function fails." << endl;
		return false;
	}
	delete next;

	next = buffer->pop();
	if (next->type != 15 || next->data != 0 || buffer->size() != 0) {
		cout << "ERROR: Pop function fails." << endl;
		return false;
	}
	delete next;

	buffer->push(CONTRACT_HAND, 2);
	buffer->push(EXTEND_HAND);
	buffer->push(EXTEND_HAND);
	buffer->push(EXTEND_HAND);

	while (!buffer->isEmpty()) {
		next = buffer->pop();
		if (next == nullptr || next->type != EXTEND_HAND) {
			cout << "ERROR: Prioritize new fails, old values not replaced." << endl;
			return false;
		}
		delete next;
	}

	next = buffer->pop();
	if (next != nullptr) {
		cout << "ERROR: Empty buffer not returning nullptr during pop." << endl;
		return false;
	}
	delete next;

	buffer->push(CONTRACT_HAND, 2);
	buffer->push(EXTEND_HAND);
	Command* list = buffer->list();
	if (list == nullptr || list[0].type != CONTRACT_HAND || list[1].type != EXTEND_HAND) {
		cout << "ERROR: Failed to list commands." << endl;
		return false;
	}
	delete[] list;

	buffer->clear();
	if (buffer->size() != 0) {
		cout << "ERROR: Failed to clear buffer." << endl;
		return false;
	}

	delete buffer;

	buffer = new CommandBuffer(3, false);
	buffer->push(CONTRACT_HAND, 2);
	buffer->push(EXTEND_HAND);
	buffer->push(EXTEND_HAND);
	buffer->push(EXTEND_HAND);
	buffer->push(EXTEND_HAND);
	
	next = buffer->peek();
	if (next->type != CONTRACT_HAND) {
		cout << "ERROR: New values replacing old ones when they should not." << endl;
		return false;
	}
	delete next;
	delete buffer;

	return true;
}

void print(Command* list, int size) {
	for (int i = 0; i < size; ++i) {
		cout << "[type=" << list[i].type << ", data=" << list[i].data << "] ";
	}
	cout << endl;
}

int main(int argc, char* argv[]) {
	// Test suite
	if (testQueueCB()) {
		cout << "All tests passed." << endl;
	}
	else {
		cout << "Some tests failed." << endl;
	}

	// Visual example of buffer in action
	CommandBuffer* buffer = new CommandBuffer(3);
	buffer->push(CONTRACT_HAND, 2);
	buffer->push(CONTRACT_HAND, 2);
	buffer->push(EXTEND_HAND, 2);
	Command* list = buffer->list();
	print(list, buffer->size());
	delete list;
	buffer->push(CONTRACT_HAND, 2);
	list = buffer->list();
	print(list, buffer->size());
	delete list;
	delete buffer;

	return 0;
}

#pragma once
#include "Buffer.h"

template <class T>
class ElasticBuffer : public Buffer<T> {
public:
	ElasticBuffer();
	~ElasticBuffer();
	const T* get(const int index) const;
	const T* peekFront() const;
	const T* peekBack() const;
	const T* remove(const int index);
	const T* pop();
	void push(const T& item);
	void clear();
private:
	// Node for bidirectional linked list
	struct BufferNode {
		BufferNode(const T* item = nullptr) {
			this->next = nullptr;
			this->prev = nullptr;
			this->item = item;
		}
		~BufferNode() {
			delete this->item;
		}
		const T* item;
		BufferNode* next;
		BufferNode* prev;
	};

	// Bidirectional linked list of nodes
	BufferNode* head;
	BufferNode* tail;
};

template <class T>
ElasticBuffer<T>::ElasticBuffer() {
	this->head = nullptr;
	this->clear();
}

template <class T>
ElasticBuffer<T>::~ElasticBuffer() {
	this->clear();
}

template <class T>
// Returns pointer to item at target index, or nullptr if index is out of bounds or buffer is empty
const T* ElasticBuffer<T>::get(const int index) const {
	if (index < 0 || index >= Buffer<T>::numberOfItems || this->isEmpty()) {
		return nullptr;
	}

	BufferNode* temp = this->head;
	for (int i = 1; i <= index; ++i) {
		temp = temp->next;
	}

	return temp->item;
}

template <class T>
// Returns pointer to first item in buffer, or nullptr if buffer is empty
const T* ElasticBuffer<T>::peekFront() const {
	return this->isEmpty() ? nullptr : this->head->item;
}

template <class T>
// Returns pointer to last item in buffer, or nullptr if buffer is empty
const T* ElasticBuffer<T>::peekBack() const {
	return this->isEmpty() ? nullptr : this->tail->item;
}

template <class T>
// Removes item at target index from buffer and returns pointer to it
const T* ElasticBuffer<T>::remove(const int index) {
	// Return nullptr if invalid index or empty buffer
	if (index < 0 || index >= Buffer<T>::numberOfItems || this->isEmpty()) {
		return nullptr;
	}
	// Return first value
	else if (index == 0) {
		return this->pop();
	}
	// Return value besides first
	else {
		// Set temp pointer to buffer node prior to target index
		BufferNode* temp = this->head;
		for (int i = 1; i < index; ++i) {
			temp = temp->next;
		}

		// Extract data from the next buffer node
		const T* result = temp->next->item;
		temp->next->item = nullptr;

		// Delete next buffer node
		BufferNode* next = temp->next->next;
		delete temp->next;

		// Fix pointers
		temp->next = next;
		if (next != nullptr) {
			next->prev = temp;
		}

		return result;
	}
}

template <class T>
// Removes first item from buffer and returns pointer to it
const T* ElasticBuffer<T>::pop() {
	if (this->isEmpty()) {
		return nullptr;
	}

	// Extract data from node
	const T* result = this->head->item;
	this->head->item = nullptr;

	// If last item was removed, put buffer in valid clear state
	if (this->head->next == nullptr) {
		this->clear();
	}
	// Otherwise, just delete first node
	else {
		BufferNode* temp = this->head->next;
		temp->prev = nullptr;
		delete this->head;
		this->head = temp;
		--Buffer<T>::numberOfItems;
	}

	return result;
}

template <class T>
// Duplicates and appends item to the end of the buffer
void ElasticBuffer<T>::push(const T& item) {
	BufferNode* temp = new BufferNode(new const T(item));

	if (this->isEmpty()) {
		this->tail = temp;
		this->head = this->tail;
	}
	else {
		temp->prev = this->tail;
		this->tail->next = temp;
		this->tail = this->tail->next;
	}

	++Buffer<T>::numberOfItems;
}

template <class T>
// Deletes all items in buffer and sets class members to empty state
void ElasticBuffer<T>::clear() {
	// Delete all items in linked list
	BufferNode* temp;
	while (this->head != nullptr) {
		temp = this->head->next;
		delete this->head;
		this->head = temp;
	}

	this->tail = nullptr;
	Buffer<T>::numberOfItems = 0;
}
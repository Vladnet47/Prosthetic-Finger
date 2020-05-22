#pragma once
#include <iostream>
#include "Buffer.h"

template <class T>
class ElasticBuffer : public Buffer<T> {
public:
	ElasticBuffer();
	~ElasticBuffer();
	const T* get(const int index) const;
	const T* peekFront() const;
	const T* peekBack() const;
	const T* pop();
	void push(const T& item);
	int size() const;
	bool isEmpty() const;
	void clear();
private:
	struct BufferNode {
		BufferNode(const T* item = nullptr) {
			this->next = nullptr;
			this->prev = nullptr;
			this->item = item;
		}
		~BufferNode() {
			std::cout << "destructor called" << std::endl;
			delete this->item;
		}
		const T* item;
		BufferNode* next;
		BufferNode* prev;
	};

	int numberOfItems;
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
const T* ElasticBuffer<T>::get(const int index) const {
	if (index < 0 || index >= this->numberOfItems || this->isEmpty()) {
		return nullptr;
	}

	BufferNode* temp = this->head;
	for (int i = 1; i < index; ++i) {
		temp = temp->next;
	}

	return temp->item;
}

template <class T>
const T* ElasticBuffer<T>::peekFront() const {
	return this->isEmpty() ? nullptr : this->head->item;
}

template <class T>
const T* ElasticBuffer<T>::peekBack() const {
	return this->isEmpty() ? nullptr : this->tail->item;
}

template <class T>
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
		--this->numberOfItems;
	}

	return result;
}

template <class T>
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

	++this->numberOfItems;
}

template <class T>
int ElasticBuffer<T>::size() const {
	return this->isEmpty() ? 0 : this->numberOfItems;
}

template <class T>
bool ElasticBuffer<T>::isEmpty() const {
	return this->numberOfItems <= 0;
}

template <class T>
void ElasticBuffer<T>::clear() {
	// Delete all items in linked list
	BufferNode* temp;
	while (this->head != nullptr) {
		temp = this->head->next;
		delete this->head;
		this->head = temp;
	}

	this->tail = nullptr;
	this->numberOfItems = 0;
}
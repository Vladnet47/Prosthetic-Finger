#pragma once
#include "Buffer.h"

template <class T>
class FixedSizeBuffer : public Buffer<T> {
public:
	FixedSizeBuffer(const int maximumNumberOfItems, const bool replaceOld = true);
	~FixedSizeBuffer();
	const T* get(const int index) const;
	const T* peekFront() const;
	const T* peekBack() const;
	const T* pop();
	void push(const T& item);
	void clear();
	void toggleReplaceOld(const bool replaceOld);
private:
	int maximumNumberOfItems;
	const T** items;
	int start;
	int end;
	bool replaceOld;

	const int increment(const int index, const int amount = 1) const;
};

template <class T>
FixedSizeBuffer<T>::FixedSizeBuffer(const int maximumNumberOfItems, const bool replaceOld) {
	this->maximumNumberOfItems = maximumNumberOfItems < 1 ? 1 : maximumNumberOfItems;
	this->replaceOld = replaceOld;

	// Initialize items
	this->items = new const T*[maximumNumberOfItems];
	for (int i = 0; i < maximumNumberOfItems; ++i) {
		this->items[i] = nullptr;
	}
	

	this->clear();
}

// Destructor
template <class T>
FixedSizeBuffer<T>::~FixedSizeBuffer() {
	this->clear();
	delete[] this->items;
}

template <class T>
const T* FixedSizeBuffer<T>::get(const int index) const {
	if (this->isEmpty() || index < 0 || index >= this->size()) {
		return nullptr;
	}

	return this->items[this->increment(this->start, index)];
}

template <class T>
const T* FixedSizeBuffer<T>::peekFront() const {
	if (this->isEmpty()) {
		return nullptr;
	}

	return this->items[this->start];
}

template <class T>
const T* FixedSizeBuffer<T>::peekBack() const {
	if (this->isEmpty()) {
		return nullptr;
	}

	return this->items[this->increment(this->end, -1)];
}

template <class T>
const T* FixedSizeBuffer<T>::pop() {
	const T* result = this->peekFront();

	if (result != nullptr) {
		--Buffer<T>::numberOfItems;
		this->items[this->start] = nullptr;

		this->start = this->increment(this->start);
	}

	return result;
}

template <class T>
void FixedSizeBuffer<T>::push(const T& item) {
	bool isFull = this->size() == this->maximumNumberOfItems;

	// Ignore new values when buffer is full (only if instructed to in constructor)
	if (isFull && !this->replaceOld) {
		return;
	}

	if (this->items[this->end] != nullptr) {
		const T* pause = this->items[this->end];
		delete this->items[this->end];
	}

	// Copy item to prevent external pointers from affecting it, and to switch onto dynamic memory
	this->items[this->end] = new T(item);
	this->end = this->increment(this->end);

	if (isFull) {
		this->start = this->increment(this->start);
	}
	else {
		++Buffer<T>::numberOfItems;
	}
}

template <class T>
void FixedSizeBuffer<T>::clear() {
	for (int i = 0; i < this->maximumNumberOfItems; ++i) {
		if (this->items[i] != nullptr) {
			delete this->items[i];
			this->items[i] = nullptr;
		}
	}

	this->start = 0;
	this->end = 0;
	Buffer<T>::numberOfItems = 0;
}

template<class T>
void FixedSizeBuffer<T>::toggleReplaceOld(const bool replaceOld)
{
	this->toggleReplaceOld = toggleReplaceOld;
}

template <class T>
const int FixedSizeBuffer<T>::increment(const int index, const int amount) const {
	return (index + amount) % this->maximumNumberOfItems;
}
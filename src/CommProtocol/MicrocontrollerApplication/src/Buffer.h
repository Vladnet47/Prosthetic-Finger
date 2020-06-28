#pragma once

template <class T, size_t SIZE>
class Buffer {
public:
	Buffer();
	~Buffer();
	const T* get(const int index) const;
	const T* peek() const;
	const T* pop();
	void push(const T& item);
	const int size() const;
	const bool isEmpty() const;
	void clear();
private:
	T items[SIZE];
	int start;
	int end;
	int numberOfItems;

	const int incrementIndex(const int index, const int inc = 1) const;
};

template <class T, size_t SIZE>
Buffer<T, SIZE>::Buffer() {
	this->clear();
}

template <class T, size_t SIZE>
Buffer<T, SIZE>::~Buffer() {}

// Returns pointer to item at target index, or nullptr if index is out of bounds or buffer is empty
template <class T, size_t SIZE>
const T* Buffer<T, SIZE>::get(const int index) const {
	return (index < 0 || index >= this->numberOfItems) ? nullptr : &this->items[incrementIndex(this->start, index)];
}

// Returns pointer to first item in buffer, or nullptr if buffer is empty
template <class T, size_t SIZE>
const T* Buffer<T, SIZE>::peek() const {
	return this->get(0);
}

// Removes first item from buffer and returns pointer to it (pointer is only temporary, as item can get modified)
template <class T, size_t SIZE>
const T* Buffer<T, SIZE>::pop() {
	if (!this->isEmpty()) {
		const T* result = this->peek();
		this->start = this->incrementIndex(this->start);
		--this->numberOfItems;
		return result;
	}

	return nullptr;
}

// Appends item to the end of the buffer if not full.
template <class T, size_t SIZE>
void Buffer<T, SIZE>::push(const T& item) {
	// Remove first item if buffer full
	if (this->numberOfItems >= SIZE) {
		this->pop();
	}
	this->items[this->end] = item;
	this->end = this->incrementIndex(this->end);
	++this->numberOfItems;
}

// Return size of buffer
template <class T, size_t SIZE>
const int Buffer<T, SIZE>::size() const {
	return this->numberOfItems;
}

// Return true if buffer is empty
template <class T, size_t SIZE>
const bool Buffer<T, SIZE>::isEmpty() const {
	return this->numberOfItems <= 0;
}

// Deletes all items in buffer and sets class members to empty state
template <class T, size_t SIZE>
void Buffer<T, SIZE>::clear() {
	this->start = 0;
	this->end = 0;
	this->numberOfItems = 0;
}

template <class T, size_t SIZE>
const int Buffer<T, SIZE>::incrementIndex(const int index, const int inc) const {
	int newIndex = index + inc;
	while (newIndex >= SIZE) {
		newIndex -= SIZE;
	}
	return newIndex;
}

#pragma once

template <class T>
class Buffer {
public:
	virtual const T* get(const int index);
	virtual const T* peek();
	virtual const T* pop();
	virtual void push(const T& item);
	virtual const T* remove(const int index);
	int size() const;
	bool isEmpty() const;
	virtual void clear();
protected:
	int numberOfItems;
};

template <class T>
// Return item at given index
const T* Buffer<T>::get(const int index) {
	return nullptr;
}

template <class T>
// Return first item
const T* Buffer<T>::peek() {
	return nullptr;
}

template <class T>
// Remove and return item at given index
const T* Buffer<T>::remove(const int index) {
	return nullptr;
}

template <class T>
// Remove and return first item
const T* Buffer<T>::pop() {
	return nullptr;
}

template <class T>
// Add item to end
void Buffer<T>::push(const T& item) {}

template <class T>
// Return size of buffer
int Buffer<T>::size() const {
	return this->isEmpty() ? 0 : this->numberOfItems;
}

template <class T>
// Return true if buffer is empty
bool Buffer<T>::isEmpty() const {
	return this->numberOfItems <= 0;
}

template <class T>
// Clear buffer
void Buffer<T>::clear() {
	this->numberOfItems = 0;
}
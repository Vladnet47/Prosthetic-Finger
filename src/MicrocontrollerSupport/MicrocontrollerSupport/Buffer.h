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
const T* Buffer<T>::get(const int index) {
	return nullptr;
}

template <class T>
const T* Buffer<T>::peek() {
	return nullptr;
}

template <class T>
const T* Buffer<T>::pop() {
	return nullptr;
}

template <class T>
void Buffer<T>::push(const T& item) {}

template <class T>
const T* Buffer<T>::remove(const int index) {
	return nullptr;
}

template <class T>
int Buffer<T>::size() const {
	return this->isEmpty() ? 0 : this->numberOfItems;
}

template <class T>
bool Buffer<T>::isEmpty() const {
	return this->numberOfItems <= 0;
}

template <class T>
void Buffer<T>::clear() {
	this->numberOfItems = 0;
}
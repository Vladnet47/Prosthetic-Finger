#pragma once

template <class T>
class Buffer {
public:
	virtual const T* get(const int index) const;
	virtual const T* peekFront() const;
	virtual const T* peekBack() const;
	virtual const T* pop();
	virtual void push(const T& item);
	int size() const;
	bool isEmpty() const;
	virtual void clear();
protected:
	int numberOfItems;
};

template <class T>
const T* Buffer<T>::get(const int index) const {
	return nullptr;
}

template <class T>
const T* Buffer<T>::peekFront() const {
	return nullptr;
}

template <class T>
const T* Buffer<T>::peekBack() const {
	return nullptr;
}

template <class T>
const T* Buffer<T>::pop() {
	return nullptr;
}

template <class T>
void Buffer<T>::push(const T& item) {}

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
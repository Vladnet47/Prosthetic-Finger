#pragma once

template <class T>
class Buffer {
public:
	virtual const T* get(const int index) const;
	virtual const T* peekFront() const;
	virtual const T* peekBack() const;
	virtual const T* pop();
	virtual void push(const T& item);
	virtual int size() const;
	virtual bool isEmpty() const;
	virtual void clear();
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
	return 0;
}

template <class T>
bool Buffer<T>::isEmpty() const {
	return true;
}

template <class T>
void Buffer<T>::clear() {}
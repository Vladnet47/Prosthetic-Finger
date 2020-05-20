#pragma once

template <class T>
class Queue {
public:
	Queue(const int size, const bool replaceOld = true);
	~Queue();

	T* get(const int index) const;
	T* peekFront() const;
	T* peekBack() const;
	T* popFront();
	T* popBack();
	void push(const T* value);
	inline void clear();
	inline int size() const;
	inline bool isEmpty() const;
	T* list() const;
	inline void toggleReplaceOld(const bool replaceOld);

private:
	T* values;
	int start;
	int end;
	int currentSize;
	int maxSize;
	bool replaceOld;

	inline int incrementIndex(int index, int amount = 1) const;
};

// Constructor: takes size of queue and optional prioritization policy (explained above 'togglereplaceOld()')
template <class T>
Queue<T>::Queue(const int size, const bool replaceOld) {
	this->values = new T[size];
	this->maxSize = size < 1 ? 1 : size;
	this->replaceOld = replaceOld;

	this->clear();
}

// Destructor
template <class T>
Queue<T>::~Queue() {
	delete[] this->values;
}

// Returns value at given index, or nullptr if it doesn't exist
template <class T>
T* Queue<T>::get(const int index) const {
	if (this->isEmpty() || index < 0 || index >= this->size()) {
		return nullptr;
	}

	return new T(this->values[this->incrementIndex(this->start, index)]);
}

// Returns next value in buffer, or nullptr if it doesn't exist
template <class T>
T* Queue<T>::peekFront() const {
	if (this->isEmpty()) {
		return nullptr;
	}

	return new T(this->values[this->start]);
}

// Returns last value in buffer, or nullptr if it doesn't exist
template <class T>
T* Queue<T>::peekBack() const {
	if (this->isEmpty()) {
		return nullptr;
	}

	return new T(this->values[this->incrementIndex(this->end, -1)]);
}

// Returns and removes first value from buffer, or nullptr if it doesn't exist
template <class T>
T* Queue<T>::popFront() {
	T* result = this->peekFront();

	if (result != nullptr) {
		this->currentSize--;
		this->start = this->incrementIndex(this->start);
	}

	return result;
}

// Returns and removes last value from buffer, or nullptr if it doesn't exist
template <class T>
T* Queue<T>::popBack() {
	T* result = this->peekBack();

	if (result != nullptr) {
		this->currentSize--;
		this->end = this->incrementIndex(this->end, -1);
	}

	return result;
}

// Adds value to the end of the queue
template <class T>
void Queue<T>::push(const T* value) {
	bool isFull = this->size() == this->maxSize;
	
	// Ignore new values when queue is full (only if instructed to in constructor)
	if (isFull && !this->replaceOld) {
		return;
	}

	this->values[this->end] = *value;
	this->end = this->incrementIndex(this->end);

	if (isFull) {
		this->start = this->incrementIndex(this->start);
	}
	else {
		this->currentSize++;
	}
}

// Returns number of elements currently in the queue
template <class T>
int Queue<T>::size() const {
	return this->currentSize < 0 ? 0 : this->currentSize;
}

// Returns true if queue is empty, false otherwise
template <class T>
bool Queue<T>::isEmpty() const {
	return this->size() == 0;
}

// Removes all elements in queue
template <class T>
void Queue<T>::clear() {
	this->currentSize = 0;
	this->start = 0;
	this->end = 0;
}

// Returns array of elements in queue
template <class T>
T* Queue<T>::list() const {
	T* result = new T[this->size()];

	int commandIndex;
	for (int i = 0; i < this->size(); ++i) {
		commandIndex = this->incrementIndex(this->start, i);
		result[i] = this->values[commandIndex];
	}

	return result;
}

// Resets queue policy on prioritizing new values over existing. When set to true, the oldest value is removed
// from the queue to make room for newest (since queue is of set size). When set to false, the newest value is ignored.
template <class T>
void Queue<T>::toggleReplaceOld(const bool replaceOld) {
	this->replaceOld = replaceOld;
}

// Increments index by 1 while preserving rotation (when index reaches end of queue array, it goes back to 0)
template <class T>
int Queue<T>::incrementIndex(int index, int amount) const {
	return (index + amount) % this->maxSize;
}

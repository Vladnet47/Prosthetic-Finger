#pragma once
#include "Util.h"
#include "Buffer.h"

template <class T>
class ElasticBuffer : public Buffer<T> {
public:
	ElasticBuffer();
	ElasticBuffer(const ElasticBuffer<T>& other);
	~ElasticBuffer() override;
	const T* get(const int index) override;
	const T* peek() override;
	const T* remove(const int index) override;
	const T* pop() override;
	void push(const T& item) override;
	void clear() override;
private:
	// Node for bidirectional linked list
	struct BufferNode {
		BufferNode(const T& item) {
			this->next = nullptr;
			this->prev = nullptr;
			this->item = new const T(item);
		}
		~BufferNode() {
			delete this->item;
		}
		const T* item;
		BufferNode* next;
		BufferNode* prev;
	};

	// Pointers to start and end of linked list
	BufferNode* head;
	BufferNode* tail;

	// Keep track of last accessed index/node to improve nearby retrieval speeds
	BufferNode* lastAccessed;
	int lastAccessedIndex;

	BufferNode* getPointer(const int index) const;
};

template <class T>
ElasticBuffer<T>::ElasticBuffer() {
	this->head = nullptr;
	this->clear();
}

template <class T>
ElasticBuffer<T>::ElasticBuffer(const ElasticBuffer<T>& other) {
	if (*this != other) {
		this->clear();

		int count = 0;
		const T* item = other.get(count);
		while (item != nullptr) {
			this->push(item);
			++count;
			item = other.get(count);
		}
	}
}

template <class T>
ElasticBuffer<T>::~ElasticBuffer() {
	this->clear();
}

template <class T>
// Returns pointer to item at target index, or nullptr if index is out of bounds or buffer is empty
const T* ElasticBuffer<T>::get(const int index) {
	BufferNode* node = this->getPointer(index);
	if (node == nullptr) {
		return nullptr;
	}

	// Update last accessed pointer if desired node wasn't the head or tail
	if (index != 0 || index != this->size() - 1) {
		this->lastAccessed = node;
		this->lastAccessedIndex = index;
	}

	return node->item;
}

template <class T>
// Returns pointer to first item in buffer, or nullptr if buffer is empty
const T* ElasticBuffer<T>::peek() {
	return this->get(0);
}

template <class T>
// Removes item at target index from buffer and returns pointer to it
const T* ElasticBuffer<T>::remove(const int index) {
	const T* result = nullptr;

	if (index == 0) {
		if (this->head != nullptr) {
			// Extract data from head
			result = this->head->item;
			this->head->item = nullptr;

			// If last item was removed, put buffer in valid clear state
			if (this->head->next == nullptr) {
				this->clear();
			}
			else {
				// Otherwise, just delete first node
				BufferNode* temp = this->head->next;
				temp->prev = nullptr;
				delete this->head;
				this->head = temp;
				--Buffer<T>::numberOfItems;
			}

			// Don't modify last accessed, but keep pointing to the same node
			--this->lastAccessedIndex;
		}
	}
	else {
		// Get pointer to node before the one to delete
		BufferNode* node = this->getPointer(index - 1);
		if (node != nullptr) {
			BufferNode* toRemove = node->next;

			// Extract data from the next buffer node
			result = toRemove->item;
			toRemove->item = nullptr;

			// Update next/prev pointers
			node->next = toRemove->next;
			if (node->next != nullptr) {
				node->next->prev = node;
			}
			else {
				// If removing last item, update tail pointer
				this->tail = node;
			}

			delete toRemove;
			--Buffer<T>::numberOfItems;

			if (this->lastAccessed != nullptr) {
				// If deleted last accessed node, set last accessed to nullptr
				if (this->lastAccessedIndex == index) {
					this->lastAccessed = nullptr;
				}
				// If deleted earlier node, shift last accessed index left
				else if (this->lastAccessedIndex > index) {
					--this->lastAccessedIndex;
				}
			}
		}
	}

	return result;
}

template <class T>
// Removes first item from buffer and returns pointer to it
const T* ElasticBuffer<T>::pop() {
	return this->remove(0);
}

template <class T>
// Duplicates and appends item to the end of the buffer
void ElasticBuffer<T>::push(const T& item) {
	BufferNode* temp = new BufferNode(item);

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

	// Update all pointers and counts
	this->tail = nullptr;
	this->lastAccessed = nullptr;
	this->lastAccessedIndex = 0;
	Buffer<T>::numberOfItems = 0;
}

template <class T>
// Returns pointer to node at provided index, or nullptr if index is out of bounds. Utilizes
// additional pointer to last accessed item to improve lookup efficiency of nearby indeces.
typename ElasticBuffer<T>::BufferNode* ElasticBuffer<T>::getPointer(const int index) const {
	const int size = this->size();

	if (this->isEmpty() || index < 0 || index >= size) {
		return nullptr;
	}
	else if (index == 0) {
		return this->head;
	}
	else if (index == size - 1) {
		return this->tail;
	}
	else {
		// Calculate distances from all three pointers
		const int distFromLast = this->lastAccessed == nullptr ? size : Util::Math::absV(this->lastAccessedIndex - index);
		const int distFromHead = index - 0;
		const int distFromTail = size - index - 1;

		BufferNode* closest;

		// Find shortest distance, copy closest pointer, and determine direction it should move along buffer (true = towards next, false = towards previous)
		const int closestDist = Util::Math::minV(distFromLast, Util::Math::minV(distFromHead, distFromTail));
		bool moveTowardsNext;
		if (closestDist == distFromLast) {
			closest = this->lastAccessed;
			moveTowardsNext = index - lastAccessedIndex >= 0;
		}
		else if (closestDist == distFromHead) {
			closest = this->head;
			moveTowardsNext = true;
		}
		else {
			closest = this->tail;
			moveTowardsNext = false;
		}

		// Navigate pointer to index
		for (int i = 0; i < closestDist; ++i) {
			closest = moveTowardsNext ? closest->next : closest->prev;
		}

		return closest;
	}
}
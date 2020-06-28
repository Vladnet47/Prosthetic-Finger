#pragma once

template <class K, class V, size_t SIZE>
class Map {
public:
	Map();
	~Map();
	void insert(const K& key, const V& value);
	const V* get(const K& key) const;
	const bool contains(const K& key) const;
	const int size() const;
private:
	K keys[SIZE];
	V values[SIZE];
	int numberOfItems;
};

template <class K, class V, size_t SIZE>
Map<K, V, SIZE>::Map() {
	this->numberOfItems = 0;
}

template <class K, class V, size_t SIZE>
Map<K, V, SIZE>::~Map() {}

template <class K, class V, size_t SIZE>
void Map<K, V, SIZE>::insert(const K& key, const V& value) {
	if (this->size() >= SIZE) {
		return;
	}

	// Replace existing
	for (int i = 0; i < this->numberOfItems; ++i) {
		if (this->keys[i] == key) {
			this->values[i] = value;
			return;
		}
	}

	// Append to end
	this->keys[this->numberOfItems] = key;
	this->values[this->numberOfItems] = value;
	++this->numberOfItems;
}

// Returns pointer to item with given key, or nullptr if it doesn't exist. Item is not copied.
template <class K, class V, size_t SIZE>
const V* Map<K, V, SIZE>::get(const K& key) const {
	for (int i = 0; i < this->numberOfItems; ++i) {
		if (this->keys[i] == key) {
			return &this->values[i];
		}
	}

	return nullptr;
}

template <class K, class V, size_t SIZE>
const bool Map<K, V, SIZE>::contains(const K& key) const {
	for (int i = 0; i < this->numberOfItems; ++i) {
		if (this->keys[i] == key) {
			return true;
		}
	}

	return false;
}

template <class K, class V, size_t SIZE>
const int Map<K, V, SIZE>::size() const {
	return this->numberOfItems;
}

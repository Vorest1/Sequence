#pragma once
#include"Sequence.h"
#include<utility>
#include<cmath>
#include<vector>

template<typename T>
class Queue {
private:
	LinkedListSequence<T> _data;
public:
	Queue() = default;
	T Front() const;
	void Push(const T& elem);
	void Pop();
};

template<typename T>
T Queue<T>::Front() const {
	return _data.GetLast();
}

template<typename T>
void Queue<T>::Push(const T& elem) {
	return _data.Prepend(elem);
}

template<typename T>
void Queue<T>::Pop() {
	return _data.PopLast();
}

template<typename T>
class Stack {
private:
	LinkedListSequence<T> _data;
public:
	Stack() = default;
	Stack(const Stack& other) = default;
	T Front() const;
	void Push(const T& elem);
	void Pop();
};

template<typename T>
T Stack<T>::Front() const {
	return _data.GetLast();
}

template<typename T>
void Stack<T>::Push(const T& elem) {
	return _data.Append(elem);
}

template<typename T>
void Stack<T>::Pop() {
	return _data.PopLast();
}

template<typename Key, typename Value, class Comparator = std::less<Key>>
class PriorityQueue {
public:
	PriorityQueue(const Comparator& comp = Comparator());
	size_t Size() const;
	std::pair<Key, Value> Top() const;
	void Push(const Key& key, const Value& value);
	void Pop();
private:
	void SiftUp(size_t idnex);
	void SiftDown(size_t idnex);
private:
	struct _Node {
		Key key;
		Value value;
	};
private:
	ArraySequence<_Node> _data;
	Comparator _comp;
};

template<typename Key, typename Value, class Comparator>
void PriorityQueue<Key, Value, Comparator>::SiftUp(size_t index) {
	if (index == 0) {
		return;
	}
	size_t parent = (index - 1) / 2;
	if (_comp(_data[index].key, _data[parent].key)) {
		std::swap(_data[index], _data[parent]);
		SiftUp(parent);
	}
}

template<typename Key, typename Value, class Comparator>
void PriorityQueue<Key, Value, Comparator>::SiftDown(size_t index) {
	size_t left = 2 * index + 1;
	size_t right = 2 * index + 2;
	if (left >= _data.GetSize()) {
		return;
	}
	size_t important = index;
	if (_comp(_data[left].key, _data[important].key)) {
		important = left;
	}
	if (right < _data.GetSize() && (_comp(_data[right].key, _data[important].key))) {
		important = right;
	}
	if (important == index) {
		return;
	}
	std::swap(_data[index], _data[important]);
	SiftDown(important);
}

template<typename Key, typename Value, class Comparator>
PriorityQueue<Key, Value, Comparator>::PriorityQueue(const Comparator& comp) : _comp(comp) {}

template<typename Key, typename Value, class Comparator>
size_t PriorityQueue<Key, Value, Comparator>::Size() const {
	return _data.GetSize();
}

template<typename Key, typename Value, class Comparator>
std::pair<Key, Value> PriorityQueue<Key, Value, Comparator>::Top() const {
	return { _data[0].key, _data[0].value };
}

template<typename Key, typename Value, class Comparator>
void PriorityQueue<Key, Value, Comparator>::Push(const Key& key, const Value& value) {
	_data.Append({ key, value });
	SiftUp(_data.GetSize() - 1);
}

template<typename Key, typename Value, class Comparator>
void PriorityQueue<Key, Value, Comparator>::Pop() {
	if (_data.GetSize() == 1) {
		_data.PopLast();
		return;
	}
	std::swap(_data[0], _data[_data.GetSize() - 1]);
	_data.PopLast();
	SiftDown(0);
}

template<typename T>
class BlockedDeque {
private:
	ArraySequence<std::vector<T>> _data;
	size_t _left;
	size_t _right;
public:
	BlockedDeque();
	T Front() const;
	T Back() const;
	void PushFront(const T& elem);
	void PushBack(const T& elem);
	void PopFront();
	void PopBack();
};


template<typename T>
BlockedDeque<T>::BlockedDeque() : _left(0), _right(0) {
	for (size_t i = 0; i < 5; ++i) {
		_data.Append(std::vector<T>(10));
	}
}

template<typename T>
T BlockedDeque<T>::Front() const {
	return _data[_left / 10][_left % 10];
}

template<typename T>
T BlockedDeque<T>::Back() const {
	return _data[(_right - 1) / 10][(_right - 1) % 10];
}

template<typename T>
void BlockedDeque<T>::PushFront(const T& elem) {
	if (_left == 0) {
		_data.Prepend(std::vector<T>(10));
		_left += 10;
		_right += 10;
	}
	--_left;
	_data[_left / 10][_left % 10] = elem;
}

template<typename T>
void BlockedDeque<T>::PushBack(const T& elem) {
	if (_right == _data.GetSize() * 10) {
		_data.Append(std::vector<T>(10));
	}

	_data[_right / 10][_right % 10] = elem;
	++_right;
}

template<typename T>
void BlockedDeque<T>::PopFront() {
	++_left;
}

template<typename T>
void BlockedDeque<T>::PopBack() {
	--_right;
}

template<typename T>
class Vector {
private:
	DynamicArray<T> _data;
public:
	Vector(const T* data, size_t size);
	Vector& operator *=(const T& elem);
	Vector& operator +=(const Vector& other);
	T Abs() const;
	size_t GetSize() const;
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
};

template<typename T>
T operator*(const Vector<T>& first, const Vector<T>& second) {
	size_t size = std::min(first.GetSize(), second.GetSize());
	T sum = T();
	for (size_t i = 0; i < size; ++i) {
		sum += first[i] * second[i];
	}
	return sum;
}

template<typename T>
Vector<T>::Vector(const T* data, size_t size) : _data(data, size) {}

template<typename T>
T Vector<T>::Abs() const {
	T sum = T();
	for (size_t i = 0; i < _data.GetSize(); ++i) {
		sum += _data[i] * _data[i];
	}
	return std::sqrt(sum);
}

template<typename T>
size_t Vector<T>::GetSize() const {
	return _data.GetSize();
}


template<typename T>
T& Vector<T>::operator[](size_t index) {
	return _data[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const {
	return _data[index];
}


template<typename T>
Vector<T>& Vector<T>::operator*=(const T& elem) {
	for (size_t i = 0; i < _data.GetSize(); ++i) {
		_data[i] *= elem;
	}
	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator+=(const Vector& other) {
	size_t old_size = _data.GetSize();
	if (_data.GetSize() < other.GetSize()) {
		_data.Resize(other._data.GetSize());
	}
	for (size_t i = old_size; i < other._data.GetSize(); ++i) {
		_data[i] = T();
	}
	for (size_t i = 0; i < other._data.GetSize(); ++i) {
		_data[i] += other._data[i];
	}
	return *this;
}
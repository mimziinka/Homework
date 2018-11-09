#pragma once
#include "LinkedList.h"

class DynamicArray {
private:
	LinkedList *data;
	size_t capacity;
	size_t size;

public:
	DynamicArray() 
		: capacity(2), size(0), data(new LinkedList[capacity]) {
	}

	~DynamicArray() {
		Clear();
	}

	DynamicArray(DynamicArray const &other) {
		Copy(other);
	}

	DynamicArray& operator=(const DynamicArray &other) {
		if (this != &other) {
			Clear();
			Copy(other);
		}

		return *this;
	}


public:
	void Clear() {
		delete[] data;

		NullVariables();
	}

	void NullVariables() {
		data = nullptr;
		capacity = 0;
		size = 0;
	}

	LinkedList GetAt(size_t index) const {
		if (index >= size)
			throw std::out_of_range("Invalid index");

		return data[index];
	}

	void SetAt(size_t index, LinkedList value) {
		if(index >= size)
			throw std::out_of_range("Invalid index");

		data[index] = value;
	}

	size_t GetSize() const {
		return size;
	}

	void Push_Back(LinkedList element) {
		if (size >= capacity)
			Resize();

		data[size++] = element;
	}

	void PopAt(size_t index) {
		this[index].data->Clear();
		if (index == size - 1)
			--size;
		else {
			for (size_t i = index + 1; i < size - 1; i++)
				data[i - 1] = data[i];
		}

		--size;
	}

	void Split(LinkedList list, size_t index) {
		LinkedList::Node *temp = list.first;

		for (size_t i = 0; i < index; i++) {
			temp = list.first->next;
		}

		temp->next->prev = nullptr;
		temp->prev->next = nullptr;

		LinkedList newList;
		newList.CloneChain(temp->next, newList.first, newList.last);

		delete[] temp;
	}


public:
	LinkedList& operator[](size_t index) {
		return data[index];
	}

	const LinkedList& operator[](size_t index) const {
		return data[index];
	}

private:
	void Copy(const DynamicArray &other) {
		data = new LinkedList[other.capacity];

		for (size_t i = 0; i < other.size; i++) {
			data[i] = other.data[i];
		}

		capacity = other.capacity;
		size = other.size;
	}

	void Resize() {
		LinkedList *newData = new LinkedList[capacity*2];

		for (size_t i = 0; i < size; i++) {
			newData[i] = data[i];
		}

		delete[] data;
		data = newData;
		capacity *= 2;
	}
};

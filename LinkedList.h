#pragma once
#include <iostream>

#include <assert.h>

//TODO
//Seperate list after removal of person in the middle

//Check if the students's uni is suitable when pushing back

struct Student {
	char * name;
	char * uni;
	
};

//double linked list

class LinkedList {
public:
	struct Node {
		Student data;
		struct Node *next;
		struct Node *prev;

		bool HasSuccessor() const {
			return next != nullptr;
		}
	};

public:
	Node *first;
	Node *last;
	size_t size;

public:
	LinkedList() {
		NullVariables();
	}

	LinkedList(LinkedList const &other) {
		NullVariables();
		Copy(other);
	}

	LinkedList& operator= (const LinkedList &other) {
		if (this != &other) {
			Clear();
			Copy(other);
		}

		return *this;
	}

	~LinkedList() {
		Clear();
	}

public:
	void NullVariables() {
		size = 0;
		first = 0;
		last = 0;
	}

	size_t GetSize() const {
		return size;
	}

	bool IsEmpty() const {
		return size == 0;
	}

	void CloneChain(Node *first, Node *clonedStart, Node *clonedEnd) {
		clonedStart = nullptr;
		clonedEnd = nullptr;

		if (first == nullptr) return;

		Node *newChain = nullptr;

		try {
			newChain = new Node;
			newChain->data = first->data;

			Node *nextToCopy = first->next;

			Node *needToCopy = newChain;

			while (nextToCopy) {
				needToCopy->next = new Node;
				needToCopy->next->data = nextToCopy->data;
				needToCopy = needToCopy->next;
				nextToCopy = nextToCopy->next;
			}

			clonedStart = newChain;
			clonedEnd = needToCopy;
		}

		catch (std::bad_alloc&) {
			DestroyChain(newChain);
		}

		//needs to be modified
	}

	void DestroyChain(Node *first) {
		Node *current = first;
		Node *old = first;

		while (current) {
			old = current;
			current = current->next;
			delete old;
		}
	}

	bool Copy(LinkedList const & other) {
		if (other.IsEmpty()) return true;

		Node *newChainStart, *newChainEnd;
		CloneChain(other.first, newChainStart, newChainEnd);

		if (!newChainStart)
			return false;

		if (size == 0)
			first = newChainStart;
		else
			last->next = newChainStart;

		last = newChainEnd;
		size += other.size;

		return newChainStart != nullptr;
	}

	void Clear() {
		DestroyChain(first);
		NullVariables();
	}

	void PushBack(Student const &value) {
		//no constructor in struct
		//needs to be redacted
		Node *newNode = new Node;
		newNode->data = value;
		
		if (IsEmpty()) {
			first = last = newNode;
		}

		else {
			this->last->next = newNode;
			newNode->prev = this->last;
			this->last = newNode;
		}

		++size;

		//needs to be modified
		//include the filter function
	}

	void PopBack() {
		if (!IsEmpty())
			RemoveAt(size - 1);

	}
	
	void RemoveAt(size_t index) {
		if (index >= size) {
			throw std::out_of_range("Invalid index.");
		}

		if (index == 0)
			PopFront();
		else {
			assert(this->GetSize() >= 2);
			Node *nodeBeforeIndex = FindNodeAt(index - 1);

			assert(nodeBeforeIndex != nullptr);

			Node *nodeAtIndex = nodeBeforeIndex->next;

			if (index == size - 1)
				last = nodeBeforeIndex;

			nodeBeforeIndex->next = nodeAtIndex->next;
			nodeAtIndex->next->prev = nodeBeforeIndex;

			delete nodeAtIndex;

			--size;
		}
	}
	
	Node* FindNodeAt(size_t index) const {
		if (index < 0 || index >= this->size)
			return nullptr;

		Node *p = first;

		for (size_t i = 0; i < index; ++i) {
			p = p->next;
		}

		return p;
	}

	void PopFront() {
		if (IsEmpty())
			return;

		Node *oldFirst = first;
		first = first->next;

		if (first == nullptr)
			last = nullptr;

		--size;

		delete oldFirst;
	}
	
	void PopByName(const char * name) {
		Node *temp = first;
		
		for (size_t i = 0; i < size; i++) {
			if(strcmp(temp->data.name, name))
				temp = temp->next;
			else {
				RemoveAt(i);
				break;
			}
		}
	}
	
	Student& At(size_t index) {
		if (index >= size)
			throw std::out_of_range("Invalid index");

		return FindNodeAt(index)->data;
	}
	
	const Student& At(size_t index) const {
		if (index >= size)
			throw std::out_of_range("Invalid index");

		return FindNodeAt(index)->data;
	}

	bool isValidStudent(Student prevStudent, Student newStudent) {
		if (!(strcmp(prevStudent.uni, "fmi")) && !(strcmp(newStudent.uni, "unss"))) 
			return 0;
		if (!(strcmp(prevStudent.uni, "tu")) && !(strcmp(newStudent.uni, "fmi"))) 
			return 0;
		if (!(strcmp(prevStudent.uni, "unss")) && !(strcmp(newStudent.uni, "tu"))) 
			return 0;

		return 1;
	}

	void Merge(LinkedList *&left, LinkedList *&right) {
		left->last->next = right->first;
		right->first->prev = left->last;
		left->last = right->last;

		DestroyChain(right->first);
	}

private: 

};


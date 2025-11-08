#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {

	// Struct for each Node
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};

	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

public:
	// Behaviors
	void printForward() const {
		const Node* curNode = head;
		while (curNode) {
			std::cout << curNode->data << " ";
			curNode = curNode->next;
		}
		std::cout << std::endl;
	}
	void printReverse() const {
		const Node* curNode = tail;
		while (curNode) {
			std::cout << curNode->data << " ";
			curNode = curNode->prev;
		}
		std::cout << std::endl;
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node* getHead() {
		return head;
	}
	const Node* getHead() const {
		return head;
	}
	Node* getTail() {
		return tail;
	}
	const Node* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		Node* newHead = new Node{data, nullptr, head};

		if (head) {
			head->prev = newHead;
		}
		else {
			tail = newHead;
		}

		head = newHead;
		count++;
	}
	void addTail(const T& data) {
		Node* newTail = new Node{data, tail, nullptr};

		if (tail) {
			tail->next = newTail;
		}
		else {
			head = newTail;
		}

		tail = newTail;
		count++;
	}

	// Removal
	bool removeHead() {
		if (!head) {
			return false;
		}

		Node* nextNode = head->next;
		delete head;
		head = nextNode;

		if (head) {
			head->prev = nullptr;
		}
		else {
			tail = nullptr;
		}

		count--;

		return true;
	}
	bool removeTail() {
		if (!tail) {
			return false;
		}

		Node* prevNode = tail->prev;
		delete tail;
		tail = prevNode;

		if (tail) {
			tail->next = nullptr;
		}
		else {
			head = nullptr;
		}

		count--;

		return true;
	}
	void clear() {
		while (removeHead()) {}
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) {
			return *this;
		}

		clear();

		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;

		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}

		clear();

		Node* prevNode = nullptr;
		Node* curNode = rhs.head;

		while (curNode) {
			Node* newNode = new Node{curNode->data, prevNode, nullptr};
			if (prevNode) {
				prevNode->next = newNode;
			}
			else {
				head = newNode;
			}

			prevNode = newNode;
			curNode = curNode->next;
		}

		tail = prevNode;
		count = rhs.count;

		return *this;
	}

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}
	LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(list.count) {
		Node* prevNode = nullptr;
		Node* curNode = list.head;

		while (curNode) {
			Node* newNode = new Node{curNode->data, prevNode, nullptr};
			if (prevNode) {
				prevNode->next = newNode;
			}
			else {
				head = newNode;
			}
			prevNode = newNode;
			curNode = curNode->next;
		}

		tail = prevNode;
	}
	LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {
		Node* curNode = head;
		while (curNode) {
			Node* nextNode = curNode->next;
			delete curNode;
			curNode = nextNode;
		}

		head = nullptr;
		tail = nullptr;
		count = 0;
	}
};



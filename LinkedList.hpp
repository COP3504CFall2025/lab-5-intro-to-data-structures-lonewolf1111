#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const;
	void printReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const {return count;}
	Node<T>* getHead() {return head;}
	const Node<T>* getHead() const {return head;}
	Node<T>* getTail() {return tail;}
	const Node<T>* getTail() const {return tail;}

	// Insertion
	void addHead(const T& data);
	void addTail(const T& data);

	// Removal
	bool removeHead();
	bool removeTail();
	void Clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	virtual ~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;

};


//  ---------------------------Code implementations here------------------------------------------
template <typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	if(!list.head) return;
	head = new Node(list.head->data,nullptr,nullptr);
	Node<T>* temp = head;
	Node<T>* tempList = list.head;
	while (tempList->next != nullptr) {
		Node<T>* nextNode = new Node(tempList->data, temp, nullptr);
		temp->next = nextNode;

		temp = nextNode;
		tempList = tempList->next;
	}
	tail = temp;
	count = list.count;
}


template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	if(this == &rhs) return *this;
	
	this->Clear();

	if (rhs.head == nullptr) {
        head = nullptr;
        tail = nullptr;
        count = 0;
        return *this;
    }

	head = new Node(rhs.head->data,nullptr,nullptr);
	
	Node<T>* temp = head;
	Node<T>* tempList = rhs.head->next;
	while(tempList != nullptr) {
		Node<T>* nextNode = new Node(tempList->data, temp, nullptr);
		temp->next = nextNode;

		temp = nextNode;
		tempList = tempList->next;
	}
	
	tail = temp;
	count = rhs.count;

	return *this;
}

template <typename T>
LinkedList<T>:: ~LinkedList() {
	Clear();
}

template <typename T>
LinkedList<T> :: LinkedList (LinkedList&& other) noexcept  {
	head = other.head;
	tail = other.tail;
	count = other.count;
	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept{
	if (this == &other) return *this;
	this->Clear();
	head = other.head;
	tail = other.tail;
	count = other.count;
	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;
	return *this;
}

template <typename T>
void LinkedList<T>::printForward() const {
	Node<T>* temp = head;
	while(temp != nullptr) {
		std::cout << temp->data << std::endl;
		temp = temp->next;
	}
}

template <typename T>
void LinkedList<T>::printReverse() const {
	Node<T>* temp = tail;
	while(temp != nullptr) {
		std::cout << temp->data << std::endl;
		temp = temp->prev;
	}
}

template <typename T>
void LinkedList<T>::addHead(const T& data) {
	Node<T>* newHead = new Node(data, nullptr, head);
	if( head != nullptr) {
		head->prev = newHead;
	} else {
		tail = newHead;
	}
	head = newHead;
	count++;
}

template <typename T>
void LinkedList<T>::addTail(const T& data) {
	Node<T>* newTail = new Node(data, tail, nullptr);

	if(tail != nullptr) {
		tail -> next = newTail;
	} else {
		head = newTail;
	}
	tail = newTail;
	count++;
}

template <typename T>
bool LinkedList<T>::removeHead() {
	if(head == nullptr) return false;
	Node<T>* temp = head;
	if(head-> next != nullptr) {
		head = head->next;
		head->prev = nullptr;
	} else {
		tail = nullptr;
	}
	delete temp;

	count --;
	return true;
	
}

template <typename T>
bool LinkedList<T>::removeTail() {
	if(tail == nullptr) return false;
	Node<T>* temp = tail;
	if(tail->prev != nullptr) {
		tail = tail->prev;
		tail->next = nullptr;
	} else {
		head = nullptr;
	}
	
	delete temp;
	count --;
	return true;
}

//use your helper functions lmao
template <typename T>
void LinkedList<T>::Clear() {
	while(removeHead());
}
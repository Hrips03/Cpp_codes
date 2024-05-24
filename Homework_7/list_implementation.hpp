#pragma once
#include <utility>
#include <exception>
#include <cstddef>
#include <cassert>


template<typename T>
class DoublyLinkedList {

	struct Node {
		T data;
		Node* prev = nullptr;
		Node* next = nullptr;
		Node(const T& data_) : data(data_), prev(nullptr), next(nullptr) {};
	};
public:
	class iterator {
		Node* m_curr = nullptr;
		Node* m_prev = nullptr;

	public:
		iterator(Node* d): m_curr(d),m_prev(m_curr->prev) {}
		iterator(Node* curr, Node* prev) : m_curr(curr), m_prev(prev) {}

		iterator& operator++();
		iterator operator++(int);
		T& operator*();
		iterator& operator--();
		iterator operator--(int);
        bool operator!=(const iterator& other);
	};


	DoublyLinkedList() = default;
	DoublyLinkedList(const DoublyLinkedList<T>&);
	DoublyLinkedList(DoublyLinkedList<T>&&);
	DoublyLinkedList(std::initializer_list<T> il);
	~DoublyLinkedList();


	void push_back(const T&);
	void push_front(const T&);
	void erase_back();
	void erase_front();

	iterator begin();
	iterator end();

	bool isEmpty() const;


	template<typename U, typename Out>
	friend Out& operator<<(Out&, const DoublyLinkedList<U>&);

	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
	DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&&);

private:
	Node* head = nullptr;
	Node* tail = nullptr;
};

#include "List.inl"


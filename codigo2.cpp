#pragma once

#include <cassert>
#include <iostream>


template <typename T>
class List
{
public:
	virtual ~List() {};
	int size() const; 
	virtual T &operator[](int pos) = 0;  
	virtual void insert(int pos, T val) = 0;
	void append(T val);
	void prepend(T val);
	virtual T remove(int pos) = 0;
protected:
	int sz{0};
};

template <typename T>
int List<T>::size() const
{
	return this->sz;
}

template <typename T>
void List<T>::append(T val)
{
	insert(sz, val);
}

template <typename T>
void List<T>::prepend(T val)
{
	insert(0, val);
}


template <typename T>
class LinkedList : public List<T>
{
	struct Node {
		T val;
		Node *next;
		explicit Node(T v, Node *nxt = nullptr): val{v}, next{nxt} { }
		explicit Node(Node *nxt = nullptr): next{nxt} { }
	};

public:
	LinkedList(): head{nullptr} {}
	~LinkedList()
	{
		while (head)
		{
			Node *tmp = head;
			head = head->next;
			delete tmp;
		}
	}

	T &operator[](int pos) override
	{
		Node *n = locate(pos);
		assert(n != nullptr);
		return n->val;
	}

	void insert(int pos, T val) override
	{
		assert(pos >= 0 && pos <= this->sz);
		if (pos == 0)
		{
			head = new Node(val, head);
		}
		else
		{
			Node *prev = locate(pos - 1);
			prev->next = new Node(val, prev->next);
		}
		this->sz++;
	}

	T remove(int pos) override
	{
		assert(pos >= 0 && pos < this->sz);
		Node *toRemove = nullptr;
		T value;
		if (pos == 0)
		{
			toRemove = head;
			head = head->next;
		}
		else
		{
			Node *prev = locate(pos - 1);
			toRemove = prev->next;
			prev->next = toRemove->next;
		}
		value = toRemove->val;
		delete toRemove;
		this->sz--;
		return value;
	}

	void merge(LinkedList<T> *other)
	{
		if (other->sz == 0) return;
		if (this->sz == 0)
		{
			this->head = other->head;
		}
		else
		{
			Node *n = locate(this->sz - 1);
			n->next = other->head;
		}
		this->sz += other->sz;
		other->head = nullptr;
		other->sz = 0;
	}

	LinkedList<T> *split()
	{
		int half = this->sz / 2;
		Node *curr = head;
		for (int i = 1; i < half; ++i)
			curr = curr->next;

		LinkedList<T> *second = new LinkedList<T>();
		if (curr)
		{
			second->head = curr->next;
			curr->next = nullptr;
		}
		second->sz = this->sz - half;
		this->sz = half;
		return second;
	}

private:
	Node *locate(int pos)
	{
		assert(pos >= 0 && pos < this->sz);
		Node *n = head;
		for (int i = 0; i < pos; ++i)
			n = n->next;
		return n;
	}

	Node *head;
};


enum TYPE {
	STACK = 0, 
	QUEUE = 1  
};

template <typename T>
class SQ
{
public:
	TYPE Type() const { return type; }

	SQ(TYPE t): type{t}, data{new LinkedList<T>()} { }

	int size() const { return data->size(); }

	const T &peek()
	{
		if (type == STACK)
			return (*data)[0];
		else
			return (*data)[0];
	}

	void push(T val)
	{
		if (type == STACK)
			data->prepend(val);
		else
			data->append(val);
	}

	T pop()
	{
		if (data->size() == 0) return T();
		if (type == STACK)
			return data->remove(0);
		else
			return data->remove(0);
	}

	void transform()
	{
		type = (type == STACK) ? QUEUE : STACK;
	}

	SQ<T> *split()
	{
		LinkedList<T> *secondData = data->split();
		SQ<T> *second = new SQ<T>(type);
		delete second->data;
		second->data = secondData;
		return second;
	}

	void merge(SQ<T> *other)
	{
		data->merge(other->data);
	}

private:
	TYPE type;
	LinkedList<T> *data;
};

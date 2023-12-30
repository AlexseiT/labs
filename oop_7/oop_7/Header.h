#pragma once
#include <iostream>
#include <string>
#include <time.h>

template<typename T>
class LIST
{
public:
LIST();
virtual void Input(T data) {};
virtual void Create() {};
virtual int Size() { return 0; };
virtual void Deleted() {};
virtual void Clear() {};
virtual T& operator[](int i) {
	T d = 0;
	return d;
};
protected:
};

template<typename T>
LIST<T>::LIST()
{
}

//STACK 
template<typename T>
class STACK : public LIST<T>
{
public:
	STACK();
	STACK(T data , STACK* next);
	void Input(T data);
	void Deleted();
	void Clear();
	int Size() { return size; }
	T& operator[](int i);
private:
	STACK* next;
	STACK<T>* head;
	T data;
	int size;
};

template<typename T>
STACK<T>::STACK()
{
	data = T();
	next = NULL;
	head = NULL;
	size = 0;
}

template<typename T>
STACK<T>::STACK(T data ,STACK* next)
{
	this->data = data;
	this->next = next;
}

template<typename T>
void STACK<T>::Input(T data)
{
	head = new STACK<T>(data, head);
	size++;
}
template<typename T>

void STACK<T>::Deleted()
{
	STACK<T>* t = head;
	head = head->next;
	delete t;
	size--;
}

template<typename T>
void STACK<T>::Clear()
{
	while (size)
	{
		Deleted();
	}
}
template<typename T>
T& STACK<T>::operator[](int i)
{
	if (i < 0 || i >= size) throw i;
	int count = 0;
	STACK<T>* t = this->head;

	while (t != NULL)
	{
		if (count == i)
		{
			return t->data;
		}
		t = t->next;
		count++;
	}
} 

//QUEUE
template<typename T>
class QUEUE : public LIST<T>
{
public:
	QUEUE();
	QUEUE(QUEUE* next);
	void Input(T data);
	void Create();
	void Deleted();
	void Clear();
	int Size() { return size; }
	T& operator[](int i);
private:
	QUEUE* next;
	QUEUE<T>* head;
	QUEUE<T>* tail;
	T data;
	int size;
};

template<typename T>
QUEUE<T>::QUEUE()
{
	data = T();
	size = 0;
}

template<typename T>
void QUEUE<T>::Create()
{
	head = new QUEUE<T>;
	head->next = NULL;
	tail = head;
}

template<typename T>
void QUEUE<T>::Input(T data)
{
	tail->data = data;
	tail->next = new QUEUE<T>;
	tail = tail->next;
	tail->next = NULL;
	size++;
}

template<typename T>
void QUEUE<T>::Deleted()
{
	QUEUE<T>* t = head;
	head = head->next;
	delete t;
	size--;
}

template<typename T>
void QUEUE<T>::Clear()
{
	while (size)
	{
		Deleted();
	}
}

template<typename T>
T& QUEUE<T>::operator[](int i)
{
	if (i < 0 || i >= size) throw i;
	int count = 0;
	QUEUE<T>* t = this->head;

	while (t != NULL)
	{
		if (count == i)
		{
			return t->data;
		}
		t = t->next;
		count++;
	}
}
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class list
{

public:
	list();
	~list();

	void push_back(T data); // Метод, + в конец списка.
	void delete_1();
	void clear_list();

	//void insert(T val, int index);
	//void remove(int index);
	//void push_front(T data);

	int GetSize() { return size; }
	T& operator[](const int index);

private:

	template<typename T>
	class node
	{
	public:
		node* next;
		T data;
		node(T data = T(), node* next = NULL)
		{
			this->data = data;
			this->next = next;
		}
	};
	int size;
	node<T>* head;
};

//-----------------------------------------------------------------

template<typename T>
list<T>::list()
{
	size = 0;
	head = NULL;
}

template<typename T>
list<T>::~list() // деструктор
{
	clear_list();
}

//---------------------------------Методы---------------------------------
template<typename T>
void list<T>::push_back(T data)     // реализация
{
	if (head == NULL) {
		head = new node<T>(data);
	}
	else
	{
		node<T>* cur = this->head;
		while (cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = new node<T>(data);
	}

	size++;
}

template<typename T>
T& list<T>::operator[](const int index)
{
	int count = 0;
	node<T>* cur = this->head;

	while (cur != NULL)
	{
		if (count == index)
		{
			return cur->data;
		}
		cur = cur->next;
		count++;
	}
}

template<typename T>
void list<T>::delete_1()
{
	node<T>* temp = head;

	head = head->next;

	delete temp;

	size--;
}

template<typename T>
void list<T>::clear_list()
{
	while (size)
	{
		delete_1();
	}
}

/*template<typename T>
void list<T>::push_front(T data)
{
	head = new node<T>(data, head);
	size++;
}
*/

void Write_list(list<int> lst)
{
	for (int i = 0; i < lst.GetSize(); i++) {
		cout << lst[i] << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");



	list<int> lst;

	lst.push_back(41);
	lst.push_back(30);
	lst.push_back(45);
	lst.push_back(40);
	lst.push_back(38);

	Write_list(lst);
	lst.delete_1();

	cout << "------------------" << endl;

	Write_list(lst);
	lst.clear_list();

	cout << "------------------" << endl;
	
	/*lst.push_front(1);
	lst.push_front(2);
	lst.push_front(3);*/
	Write_list(lst);

	return 0;
};
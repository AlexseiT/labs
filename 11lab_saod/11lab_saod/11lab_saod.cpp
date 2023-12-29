#include <iostream>
#include <string>
#include <clocale>
#include <ctime>
using namespace std;

struct st {
	int data;
	st* next;
};

void stack_push(st** head, int a) { // добавление элемента
	st* p;
	p = new st();
	p->data = a;
	if (head == NULL) {
		*head = p;
	}
	else
	{
		p->next = *head;
		*head = p;
	}
}

st* Fill_list_inc(int n);
st* Fill_list_dec(int n);
st* Fill_list_rand(int n);

void show_list(st* head); 
void deleted_list(st* head); 
void control(st* head); 
void serial(st* head); 

int main()
{
	st* head_inc;
	head_inc = Fill_list_inc(10);

	show_list(head_inc);
	control(head_inc);
	serial(head_inc);

	st* head_dec;
	head_dec = Fill_list_dec(10);

	show_list(head_dec);
	control(head_dec);
	serial(head_dec);

	st* head_rand;
	head_rand = Fill_list_rand(10);

	show_list(head_rand);
	control(head_rand);
	serial(head_rand);

	deleted_list(head_inc);

	deleted_list(head_dec);

	deleted_list(head_rand);
}

st* Fill_list_inc(int n) {
	st* p, * pred, * h;
	h = pred = new st;
	pred->data = n;
	for (int i = n - 1; i > 0; --i) {
		p = new st;
		p->data = i;
		pred->next = p;
		pred = p;
	}
	p->next = NULL;
	return h;
}
st* Fill_list_Dec(int n) {
	st* p, * pred, * h;
	h = pred = new st;
	pred->data = 1;
	for (int i = 2; i < n + 1; ++i) {
		p = new st;
		p->data = i;
		pred->next = p;
		pred = p;
	}
	p->next = NULL;
	return h;
}
st* Fill_list_rand(int n) {
	st* p, * pred, * h;
	h = pred = new st;
	pred->data = rand() % 20;
	for (int i = 0; i < n - 1; ++i) {
		p = new st;
		p->data = rand() % 20;
		pred->next = p;
		pred = p;
	}
	p->next = NULL;
	return h;
}

void show_list(st* head) {
	st* p;
	p = head;
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

void control(st* head) {
	st* p;
	p = head;
	int s = 0;
	while (p != NULL) {
		s += p->data;
		p = p->next;
	}
	cout << s << endl;
}
void serial(st* head) {
	st* a, * b;
	a = head;
	b = head->next;
	int k = 1;
	while (b != NULL) {
		if (a->data > b->data)
			k++;
		a = b;
		b = b->next;
	}
	cout << k << endl;
}

void deleted_list(st* head) {
	st* p, * q;
	q = p = head;
	while (p != NULL) {
		p = q->next;
		delete q;
		q = p;
	}
	head = NULL;
}
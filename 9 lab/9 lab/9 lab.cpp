#include <iostream>
#include <string>
#include <clocale>

using namespace std;

struct marks { string subject; int mark; };

struct student { string family; struct marks marks[4]; };

typedef struct st {
	struct student stud;
	struct st* next;
} list;

typedef struct stDouble {
	struct student stud;
	struct stDouble* next;
	struct stDouble* pred;
} listDouble;

void fillSubjects(list* p) {
	p->stud.marks[0].subject = "Программирование";
	p->stud.marks[1].subject = "Труды";
	p->stud.marks[2].subject = "ОБЖ";
	p->stud.marks[3].subject = "Физ-ра";
}

void fillSubjects(listDouble* p) {
	p->stud.marks[0].subject = "Программирование";
	p->stud.marks[1].subject = "Труды";
	p->stud.marks[2].subject = "ОБЖ";
	p->stud.marks[3].subject = "Физ-ра";
}

void inputMarks(list* p) {
	for (int i = 0; i < 4; i++) {
		cin >> p->stud.marks[i].mark;
	}
}
void inputMarks(listDouble* p) {
	for (int i = 0; i < 4; i++) {
		cin >> p->stud.marks[i].mark;
	}
}

void printMarks(list* p) {
	for (int i = 0; i < 4; i++) {
		cout << p->stud.marks[i].subject << ": " << p->stud.marks[i].mark << " | ";
	}
}

void printMarks(listDouble* p) {
	for (int i = 0; i < 4; i++) {
		cout << p->stud.marks[i].subject << ": " << p->stud.marks[i].mark << " | ";
	}
}

list* createSimpleList() {
	string tmp;
	list* p = NULL, * pred, * first;
	first = pred = new list;

	cin >> pred->stud.family;

	fillSubjects(pred);
	inputMarks(pred);

	cin >> tmp;
	p = new list;

	while (tmp != "0") {


		p->stud.family = tmp;
		fillSubjects(p);
		inputMarks(p);
		pred->next = p;
		pred = p;

		cin >> tmp;
		p = new list;
	}

	p = pred;
	p->next = NULL;
	return first;
}

listDouble* createDoubleList() {
	string tmp;
	listDouble* p = NULL, * pred, * first, * r = NULL;
	first = pred = new listDouble;
	pred->pred = NULL;
	cin >> pred->stud.family;

	fillSubjects(pred);
	inputMarks(pred);

	cin >> tmp;
	p = new listDouble;

	while (tmp != "0") {

		p->stud.family = tmp;
		fillSubjects(p);
		inputMarks(p);
		pred->next = p;
		pred->pred = r;
		r = pred;
		pred = p;

		cin >> tmp;
		p = new listDouble;
	}

	pred->pred = r;
	pred->next = NULL;
	return first;
}

void printList(list* head) {
	list* p;
	p = head;
	while (p != NULL) {
		cout << p->stud.family << " \t";
		printMarks(p);
		cout << endl;
		p = p->next;
	}
}

void printList(listDouble* head) {
	listDouble* p;
	p = head;
	while (p != NULL) {
		cout << p->stud.family << " \t";
		printMarks(p);
		cout << endl;
		p = p->next;
		p->pred;
	}
}

list* sortList(list* head) {
	list* a, * b, * tmp, * pred;

	bool swap = true;

	if (head == NULL)
		return head;

	while (swap) {
		swap = false;
		a = pred = head;
		b = head->next;

		while (b != NULL) {
			if (a->stud.family > b->stud.family) {
				if (pred == a)
					head = b;
				else
					pred->next = b;

				a->next = b->next;
				b->next = a;

				tmp = a, a = b, b = tmp;
				swap = true;
			}
			pred = a;
			a = a->next;
			b = b->next;
		}
	}

	return head;
}

void removeItem(listDouble* a) {

	listDouble* pred = a->pred;
	listDouble* next = a->next;

	if (pred != NULL) {
		pred->next = next;
	}
	if (next != NULL) {
		next->pred = pred;
	}


	delete a;
}

listDouble* searchItems(listDouble* head) {
	listDouble* p = head;
	listDouble* next;
	bool del;
	while (p != NULL) {
		del = false;
		next = p->next;
		for (int i = 0; i < 4; i++) {
			if (p->stud.marks[i].mark < 3) {

				if (p->pred == NULL) {
					head = head->next;
				}
				removeItem(p);
				p = next;
				del = true;
				break;
			}
		}

		if (!del) {
			p = p->next;
		}

	}

	return head;
}

int main() {

	//1

	setlocale(LC_ALL, "Russian");

	list* head;

	head = createSimpleList();
	printList(head);

	cout << endl << endl;

	head = sortList(head);
	printList(head);

	head = NULL;

	//2

	listDouble* first;

	first = createDoubleList();
	printList(first);

	cout << endl << endl;

	first = searchItems(first);
	printList(first);

	return 0;
}
#include <iostream>
#include <ctime>
using namespace std;
int M = 0, C = 0;

struct st
{
    int data;
    struct st* next;
    struct st* prev;
};

struct st* priority(struct st* head);

struct st* merge(struct st* first, struct st* second) {
    if (!first)
        return second;

    if (!second)
        return first;

    if (first->data < second->data)
    {
        M++;
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        M++;
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

struct st* sort(struct st* head) {

}

void put(struct st** head, int data) {
    struct st* temp = (struct st*)malloc(sizeof(struct st));

    temp->data = data;
    temp->next = temp->prev = NULL;

    if (!(*head))
        (*head) = temp;
    else
    {
        temp->next = *head;
        (*head)->prev = temp;
        (*head) = temp;
    }
}

struct st* priority(struct st* head) {
    struct st* a = head, * b = head;
    while (a->next && a->next->next) {
        a = a->next->next;
        b = b->next;
    }
    struct st* temp = b->next;
    b->next = NULL;
    return temp;
}

st* create_rand(struct st* head, int n) {
    int temp;
    srand(time(NULL));
    for (int i = 0; i < n; ++i)
    {
        temp = rand() % 10;
        put(&head, temp);
    }
    return head;
}

st* create_inc(struct st* head, int n) {
    int temp;
    for (int i = 0; i < n; ++i)
    {
        temp = i;
        put(&head, temp);
    }
    return head;
}

st* create_dec(struct st* head, int n) {
    int temp;
    for (int i = n; i > 0; --i)
    {
        temp = i;
        put(&head, temp);
    }
    return head;
}

void deleted_list(st* head) {
    st* p, * q;
    q = head;
    p = head;
    while (p != NULL) {
        p = q->next;
        delete q;
        q = p;
    }
    head = NULL;
}

void rands(int i)
{
    struct st* head = NULL;

    head = create_rand(head, i * 100);
    head = sort(head);
    cout << "\t" << M + C << "\t";
    M = 0; C = 0;

    deleted_list(head);

}

void inc(int i)
{
    struct st* head = NULL;

    head = create_inc(head, i * 100);
    head = sort(head);

    cout << "\t" << M + C << "\t";
    M = 0; C = 0;
    deleted_list(head);

}

void dec(int i)
{
    struct st* head = NULL;

    head = create_dec(head, i * 100);
    head = sort(head);

    cout << "\t" << M + C << "\t";
    M = 0; C = 0;
    deleted_list(head);

}

int main()
{
    cout << "           Merge Sort" << endl;
    cout << "  N     Inc            Dec              Rand" << endl;
    for (int i = 1; i < 6; ++i)
    {
        cout << "  " << i * 100 << "  ";
        inc(i);
        dec(i);
        rands(i);
        cout << endl;
    }
}
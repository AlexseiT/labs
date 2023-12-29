#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <string.h>

using namespace std;

const int N = 4000;

struct Base {
    char fio[30];
    unsigned short int sum;
    char adv[22];
    char date[10];
};

struct Node {
    Base Rec;
    Node* next;
};

struct body {
    Node* head;
    Node* tail;
};

int Compare(const Base& record1, const Base& record2) {
    if (record1.sum > record2.sum) {
        return -1;
    }
    else if (record1.sum < record2.sum) {
        return 1;
    }
    for (int i = 0; i < 22; ++i) {
        if (record1.fio[i] > record2.fio[i]) {
            return -1;
        }
        else if (record1.fio[i] < record2.fio[i]) {
            return 1;
        }
    }
    return 0;
}

void Merge_Sort(Node*& S, int n) {
    int t, q, r, i, m;
    Node* a, * b, * k, * p;
    body c[2];
    a = S;
    b = S->next;
    k = a;
    p = b;
    int x = 0;
    while (p != NULL) {
        k->next = p->next;
        k = p;
        p = p->next;
    }
    t = 1;
    Node* temp1 = a, * temp2 = b;
    while (temp1 != NULL) {
        temp1 = temp1->next;
    }
    while (temp2 != NULL) {
        temp2 = temp2->next;
    }
    while (t < n) {
        c[0].tail = c[0].head = NULL;
        c[1].tail = c[1].head = NULL;
        i = 0;
        m = n;
        while (m > 0) {
            if (m >= t) q = t;
            else q = m;
            m = m - q;
            if (m >= t) r = t;
            else r = m;
            m = m - r;
            while (q != 0 && r != 0) {
                if (Compare(a->Rec, b->Rec) > 0) {
                    if (c[i].tail == NULL) {
                        c[i].tail = c[i].head = a;
                    }
                    else {
                        c[i].tail->next = a;
                        c[i].tail = a;
                    }
                    a = a->next;
                    q--;

                }
                else {

                    if (c[i].tail == NULL) {
                        c[i].tail = c[i].head = b;
                    }
                    else {
                        c[i].tail->next = b;
                        c[i].tail = b;
                    }
                    b = b->next;
                    r--;

                }
            }
            while (q > 0) {
                if (c[i].tail == NULL) {
                    c[i].tail = c[i].head = a;
                }
                else {
                    c[i].tail->next = a;
                    c[i].tail = a;
                }
                a = a->next;
                q--;
            }
            while (r > 0) {
                if (c[i].tail == NULL) {
                    c[i].tail = c[i].head = b;
                }
                else {
                    c[i].tail->next = b;
                    c[i].tail = b;
                }
                b = b->next;
                r--;
            }
            i = 1 - i;
            x++;
        }
        a = c[0].head;
        b = c[1].head;
        t = 2 * t;
    }
    c[0].tail->next = NULL;
    S = c[0].head;
}

Node* Load_File() {
    Node* root = NULL;
    ifstream file("testBase2.dat", ios::binary);
    if (not file.is_open()) {
        return NULL;
    }

    for (int i = 0; i < N; ++i) {
        Base record;
        file.read((char*)&record, sizeof(Base));
        root = new Node{ record, root };
    }
    file.close();
    return root;
}

void Print_Note(Base* record) {
    std::cout << ") " << record->fio << "| " << setw(5) << record->sum << "| " << record->adv << "| " << record->date << "\n";
}

void Main_Panel() {
    cout << endl;
    cout << "[1] Data Base" << endl;
    cout << "[2] Merge sort Data Base" << endl;
    cout << "[3] Key Search" << endl;
    cout << "[Any other] Exit" << endl;
}

void Panel() {
    cout << endl;
    cout << "[1] <---" << endl;
    cout << "[2] --->" << endl;
    cout << "[3] Last Page" << endl;
    cout << "[4] 1 Page" << endl;
    cout << "[5] 10 Page --->" << endl;
    cout << "[6] <--- 10 Page" << endl;
    cout << "[7] [Enter Page]" << endl;
    cout << "[Any other] Exit" << endl;
}

void List(Base** data, int n = N) {
    int ind = 0;
    while (true) {
        system("cls");
        std::cout << "Number" << "          Name               " << "Department" << "         Post          " << "Date of birth" << "\n";
        for (int i = 0; i < 20; i++) {
            Base* record = data[ind + i];
            cout << setw(4) << ind + i + 1;
            Print_Note(record);
        }
        Panel();
        string chose;
        cin >> chose;
        int enter;
        int str;
        switch (chose[0]) {
        case '1':
            ind -= 20;
            break;
        case '2':
            ind += 20;
            break;
        case '3':
            ind = n - 20;
            break;
        case '4':
            ind = 0;
            break;
        case '5':
            ind += 200;
            break;
        case '6':
            ind -= 200;
            break;
        case '7':
            cin >> enter;
            str = 20 * (enter - 1);
            if (str > ind) ind += str - ind;
            else if (str < ind) ind -= ind - str;
            else ind += 0;
            break;
        default:
            system("cls");
            return;
        }
        if (ind < 0) {
            ind = 0;
        }
        else if (ind > n - 20) {
            ind = n - 20;
        }
    }
}

void List1(Base** data, int n = N) {
    int ind = 0;
    while (true) {
        system("cls");
        std::cout << "Number" << "          Name               " << "Department" << "         Post          " << "Date of birth" << "\n";
        for (int i = 0; i < 20; i++) {
            Base* record = data[ind + i];
            cout << setw(4) << ind + i + 1;
            Print_Note(record);
        }
        Panel();
        string chose;
        cin >> chose;
        int enter;
        int str;
        switch (chose[0]) {
        case '1':
            ind -= 20;
            break;
        case '2':
            ind += 20;
            break;
        case '3':
            ind = n - 20;
            break;
        case '4':
            ind = 0;
            break;
        case '5':
            ind += 200;
            break;
        case '6':
            ind -= 200;
            break;
        case '7':
            cin >> enter;
            str = 20 * (enter - 1);
            if (str > ind) ind += str - ind;
            else if (str < ind) ind -= ind - str;
            else ind += 0;
            break;
        default:
            system("cls");
            return;
        }
        if (ind < 0) {
            ind = 0;
        }
        else if (ind > n - 20) {
            ind = n - 20;
        }
    }
}

int Quick(Base** A, int key) {
    int l = 0;
    int r = N - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (A[m]->sum < key) {
            l = m + 1;
        }
        else {
            r = m;
        }
    }
    if (A[r]->sum == key) {
        return r;
    }
    return -1;
}

void Search(Base** A) {
    int key;
    int n;
    int ind;
    cout << "Enter the search key (Department)" << endl;
    cin >> key;

    ind = Quick(A, key);

    if (ind == -1) {
        system("cls");
        cout << "Key not found\n";
    }
    else {
        int i;
        for (i = ind + 1; A[i]->sum == key; ++i) {}
        n = i - ind;
        List(&A[ind], n);
    }
}

void Make_Arr(Base** data, Node* Root, int n = N) {
    Node* p = Root;
    for (int i = 0; i < n; i++) {
        data[i] = &(p->Rec);
        p = p->next;
    }
}

void Main_Window(Base** data, Base** data_sort, Node* Root) {
    Node* p = Root;
    Base* r;
    while (true) {
        Main_Panel();
        string chose;
        cin >> chose;
        switch (chose[0]) {
        case '1':
            List(data);
            break;
        case '2':
            List(data_sort);
            break;
        case '3':
            Search(data_sort);
            break;
        case '4':
            while (p != NULL) {
                r = &(p->Rec);
                cout << r->fio << endl;
                p = p->next;
            }
        default:
            return;
        }
    }
}

int main() {

    Node* Root = Load_File();
    Base* data[N];
    Base* data_sort[N];

    Make_Arr(data, Root);

    Merge_Sort(Root, N);

    Make_Arr(data_sort, Root);

    Main_Window(data, data_sort, Root);

}
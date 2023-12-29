#include <iostream>
#include <fstream> 

struct List 
{
    List* next;

    char nameStudent[30];
    char surnameStudent[30];
    double markStudent;

} *head = NULL, 
  *tail = NULL;

void printList() 
{
    List* listItem = head;
    int numberStudent = 0;
    while (listItem) {
        numberStudent++;
        std::cout << numberStudent << "|" << listItem->nameStudent << " " << listItem->surnameStudent << ": " << listItem->markStudent << std::endl;
        listItem = listItem->next;
    }
}

void insertElement(char nameStudent[], char surnameStudent[], double markStudent)
{
    if (head == NULL) {
        head = new List;
        head->next = NULL;
        strcpy_s(head->nameStudent, nameStudent);
        strcpy_s(head->surnameStudent, surnameStudent);
        head->markStudent = markStudent;
        tail = head;
    }
    else {
        tail->next = new List;
        tail = tail->next;
        tail->next = NULL;
        strcpy_s(tail->nameStudent, nameStudent);
        strcpy_s(tail->surnameStudent, surnameStudent);
        tail->markStudent = markStudent;
    }
}

void deleteFirstElement() 
{
    List* first = head;
    head = head->next;
    delete first;
}

void deleteElement(int numberElement)
{
    List* listItem = head;
    for (int i = 0; i < numberElement - 2; i++)
    {
        listItem = listItem->next;
    }
    listItem->next = listItem->next->next;
}

void serialize() {
    std::ofstream ofs("StudentList.bin", std::ios::binary);
    List* listItem = head;
    while (listItem) {
        ofs.write(listItem->nameStudent, sizeof(listItem->nameStudent));
        ofs.write(listItem->surnameStudent, sizeof(listItem->surnameStudent));
        ofs.write((char*)&listItem->markStudent, sizeof(listItem->markStudent));
        listItem = listItem->next;
    }
    ofs.close();
}

void deserialize() {
    std::ifstream ifs("StudentList.bin", std::ios::binary);
    char nameStudent[30];
    char surnameStudent[30];
    double markStudent;
    while (true) {
        ifs.read(nameStudent, sizeof(nameStudent));
        ifs.read(surnameStudent, sizeof(surnameStudent));
        ifs.read((char*)&markStudent, sizeof(markStudent));
        if (ifs.eof()) {
            break;
        }
        insertElement(nameStudent, surnameStudent, markStudent);
    }
    ifs.close();
}

int main()
{
    insertElement((char *)"Alexsei", (char*)"Toodorov", 5);
    insertElement((char *)"Petr", (char*)"Tchaikovsky", 5);
    insertElement((char*)"Andrey", (char*)"Kopchick", 3);
    insertElement((char*)"Sanya", (char*)"Vernysotky", 2);
    insertElement((char*)"Schauma", (char*)"Schwarzkopf", 4);

    printList();

    deleteElement(4);

    std::cout << std::endl;
    std::cout << std::endl;

    printList();


}

//#include "List1.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

using namespace std;

struct ListOne {
    int data; // Данные, хранящиеся в узле списка
    ListOne* next;// Указатель на следующий узел в списке
};

void addToHeadL1(ListOne*& head, int value) {
    ListOne* newNode = new ListOne;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

void addToTailL1(ListOne*& head, int value) {
    ListOne* newNode = new ListOne;
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        ListOne* temp = head;
        while (temp->next != nullptr) { //поиск послед узла и добав нов
            temp = temp->next;
        }
        temp->next = newNode;
    }
}


void printList1(ListOne* head) {
    ListOne* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

bool searchL1(ListOne* head, int value) {
    ListOne* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void removeHeadL1(ListOne*& head) {
    if (head != nullptr) {
        ListOne* temp = head;
        head = head->next;
        delete temp; //освоб память
    }
}

void freeList1(ListOne*& head) { //освоб пам с головы
    while (head != nullptr) {
        removeHeadL1(head);
    }
}


ListOne* unionSets(ListOne* set1, ListOne* set2) {
    ListOne* result = nullptr;
    ListOne* current = set1;

    while (current) {
        addToHeadL1(result, current->data);
        current = current->next;
    }

    current = set2;
    while (current) {
        if (!searchL1(set1, current->data)) {
            addToHeadL1(result, current->data);
        }
        current = current->next;
    }

    return result;
}

// Функция для пересечения множеств
ListOne* intersectionSets(ListOne* set1, ListOne* set2) {
    ListOne* result = nullptr;
    ListOne* current = set1;

    while (current) {
        if (searchL1(set2, current->data)) {
            addToHeadL1(result, current->data);
        }
        current = current->next;
    }

    return result;
}

// Функция для разности множеств (set1 - set2)
ListOne* differenceSets(ListOne* set1, ListOne* set2) {
    ListOne* result = nullptr;
    ListOne* current = set1;

    while (current) {
        if (!searchL1(set2, current->data)) {
            addToHeadL1(result, current->data);
        }
        current = current->next;
    }

    return result;
}

int main() {
    ListOne* set1 = nullptr;
    ListOne* set2 = nullptr;

    // Заполнение первого множества
    addToTailL1(set1, 1);
    addToTailL1(set1, 2);
    addToTailL1(set1, 3);

    // Заполнение второго множества
    addToTailL1(set2, 3);
    addToTailL1(set2, 4);
    addToTailL1(set2, 5);

    cout << "Set 1: ";
    printList1(set1);
    cout << "Set 2: ";
    printList1(set2);

    // Объединение множеств
    ListOne* unionSet = unionSets(set1, set2);
    cout << "Union: ";
    printList1(unionSet);

    // Пересечение множеств
    ListOne* intersectionSet = intersectionSets(set1, set2);
    cout << "Intersection: ";
    printList1(intersectionSet);

    // Разность множеств (set1 - set2)
    ListOne* differenceSet = differenceSets(set1, set2);
    cout << "Difference (set1 - set2): ";
    printList1(differenceSet);

    // Освобождение памяти
    freeList1(set1);
    freeList1(set2);
    freeList1(unionSet);
    freeList1(intersectionSet);
    freeList1(differenceSet);

    return 0;
}

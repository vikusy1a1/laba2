#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Set {
    Node** table;
    int size;

    Set(int tableSize) : size(tableSize) {
        table = new Node*[size]();
    }

    int hash(int value) const {
        return value % size;
    }

    void add(int value) {
        if (contains(value)) {
            cout << "Уже есть значение в set:" << value << endl;
            return;
        }

        int index = hash(value);
        Node* newNode = new Node{value, nullptr};

        if (table[index] == nullptr) {
            table[index] = newNode; 
        } 
        else {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    void remove(int value) {
        int index = hash(value);
        Node** current = &table[index];
        while (*current!=nullptr) {
            if ((*current)->data == value) {
                Node* toDelete = *current;
                *current = (*current)->next;
                delete toDelete;
                return;
            }
            current = &((*current)->next);
        }
    }

    bool contains(int value) const {
        int index = hash(value);
        Node* current = table[index];
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    ~Set() {
        for (int i = 0; i < size; ++i) {
            Node* current = table[i];
            while (current) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
    }

    void saveToFile(const char* filename) const {
        ofstream file(filename);
        for (int i = 0; i < size; ++i) {
            Node* current = table[i];
            while (current) {
                file << current->data << endl;
                current = current->next;
            }
        }
        file.close();
    }

    void loadFromFile(const char* filename) {
        ifstream file(filename);
        int value;
        while (file >> value) {
            add(value);
        }
        file.close();
    }
};

// Функция для выполнения команды
void executeCommand(Set& set, const string& command, int value) {
    if (command == "SETADD") {
        set.add(value);
    } else if (command == "SETDEL") {
        set.remove(value);
    } else if (command == "SET_AT") {
        cout << (set.contains(value) ? "YES" : "NO") << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        cerr << "Usage: " << argv[0] << " --file <path to file> --query <command>" << endl;
        return 1;
    }

    const char* filename = argv[2];
    const string command = argv[4];
    int value = stoi(argv[5]);

    Set set(100); // Выбор размера хеш-таблицы
    set.loadFromFile(filename);

    // Пример выполнения команд
    executeCommand(set, command, value);

    set.saveToFile(filename);

    return 0;
}

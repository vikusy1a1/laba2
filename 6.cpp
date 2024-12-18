#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

const int TABLE_SIZE = 10; // Размер хеш-таблицы

// Структура для хранения ключ-значение и указателя на следующий элемент
struct HashTable {
    string key;
    string value;
    HashTable* next; // Указатель на следующий элемент в цепочке  (для обработки коллизий)
};

// Хеш-функция
int hashFunction(const string& key) {
    int hash = 0;
    for (char ch : key) {
        hash += ch; // Суммируем ASCII-коды символов ключа
    }
    return hash % TABLE_SIZE;
} 

// Добавление элемента (ключ-значение)
void insertTable(HashTable* table[], const string& key, const string& value) {
    int index = hashFunction(key);
    HashTable* newNode = new HashTable{key, value, nullptr};

    // Проверяем, есть ли уже элементы по этому индексу
    if (table[index] == nullptr) {
        table[index] = newNode; // Если нет, добавляем как первый элемент
    } else {
        // Если есть, ищем, существует ли уже элемент с таким ключом
        HashTable* temp = table[index];
        while (temp ->next != nullptr) {
            temp = temp->next;           
        }
        // Добавляем новый узел в конец списка
        temp->next = newNode;
    }
}

// Получение значения по ключу
string getValueTable(HashTable* table[], const string& key) {
    int index = hashFunction(key);
    HashTable* temp = table[index];
    
    while (temp != nullptr) {
        if (temp->key == key) {
            return temp->value; // Возвращаем значение, если ключ найден
        }
        temp = temp->next;
    }
    return "Key not found"; // Если ключ не найден
}

// Подсчет значений
void countValues(HashTable* table[], HashTable* valueCountTable[]) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashTable* entry = table[i];
        while (entry != nullptr) {
            if (entry->key == entry->value) {
                entry = entry->next;
                continue;
            }

            if (getValueTable(valueCountTable, entry->key) == "Key not found") {
                insertTable(valueCountTable, entry->key, "0");
            }

            string value = entry->value;
            int hash = hashFunction(value);
            HashTable* temp = valueCountTable[hash];
            bool found = false;
            while (temp != nullptr) {
                if (temp->key == value) {
                    temp->value = to_string(stoi(temp->value) + 1);

                    found = true;
                    break;
                }
                temp = temp->next;
            }
            if (!found) {
                insertTable(valueCountTable, value, "1");
            }
            entry = entry->next;
        }
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        HashTable* entry = table[i];
        while (entry != nullptr) {
            if (entry->key == entry->value) {
                entry = entry->next;
                continue;
            }

            for (int j = 0; j < TABLE_SIZE; j++) {
                int hash = hashFunction(entry->value);
                HashTable* temp = valueCountTable[hash];

                HashTable* entry_deep = table[j];
                if (entry_deep == nullptr) {
                    continue;
                }


                if (entry_deep->value == entry->key) {
                    temp->value = to_string(stoi(temp->value) + stoi(getValueTable(valueCountTable, entry->key)));
                    break;
                }
            }


            entry = entry->next;
        }
    }
}
void printValueCounts(HashTable* valueCountTable[]) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashTable* entry = valueCountTable[i];
        while (entry != nullptr) {
            cout << entry->key << ": " << entry->value << endl;
            entry = entry->next;
        }
    }
}

int main() {
    // Создаем таблицу
    HashTable* table[TABLE_SIZE] = { nullptr };
    HashTable* valueCountTable[TABLE_SIZE] = { nullptr };
    string key, value;
    cout << "Enter key-value pairs (key value), or 'exit' to finish: " << endl;
    while (cin >> key && key != "exit") {
        cin >> value;
        insertTable(table, key, value);
    }

    // Подсчитываем количество ключей, у которых одинаковое значение
    countValues(table, valueCountTable);

    // Выводим результат
    printValueCounts(valueCountTable);
      // Clean up memory (Important!)
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashTable* entry = table[i];
        while (entry) {
            HashTable* next = entry->next;
            delete entry;
            entry = next;
        }
    }


    return 0;
}
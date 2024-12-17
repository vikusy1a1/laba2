#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

struct Array {
    int* data;         // Указатель на массив
    int size;        
    int capacity;      // Максимальная вместимость массива
};

void initArray(Array& arr, int cap) {
    arr.data = new int[cap]; // Выделение памяти под массив
    arr.size = 0;             
    arr.capacity = cap;       // Задание начальной вместимости
}

void appendArray(Array& arr, int value) {
    if (arr.size >= arr.capacity) {
        arr.capacity *= 2;
        int* newData = new int[arr.capacity];
        for (int i = 0; i < arr.size; ++i) {
            newData[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = newData;
    }
    arr.data[arr.size++] = value;
}

void freeArray(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

bool matchPattern(const string& str, const string& pattern) {
    int sLen = str.length();
    int pLen = pattern.length();
    int sIdx = 0, pIdx = 0;
    int starIdx = -1, sTmpIdx = -1;

    while (sIdx < sLen) {
        // Если символы совпадают или паттерн содержит ?
        if (pIdx < pLen && (pattern[pIdx] == '?' || pattern[pIdx] == str[sIdx])) {
            ++sIdx;
            ++pIdx;
        }
        // Если паттерн содержит *
        else if (pIdx < pLen && pattern[pIdx] == '*') {
            starIdx = pIdx;
            sTmpIdx = sIdx;
            ++pIdx;
        }
        // Если символы не совпадают и нет *, откатываемся к последнему '*'
        else if (starIdx != -1) {
            pIdx = starIdx + 1;
            sIdx = sTmpIdx + 1;
            sTmpIdx = sIdx;
        }
        // Если символы не совпадают и нет *
        else {
            return false;
        }
    }

    // Проверяем оставшиеся символы в паттерне
    while (pIdx < pLen && pattern[pIdx] == '*') {
        ++pIdx;
    }

    return pIdx == pLen; // Проверка, достигли ли конца паттерна
}

int main() {
      string sequence, pattern;
    
    cout << "Enter the sequence: ";
    getline(cin, sequence);
    
    cout << "Enter the pattern: ";
    getline(cin, pattern);
    
    if (matchPattern(sequence, pattern)) {
        cout << "The sequence matches the pattern." << endl;
    } else {
        cout << "The sequence does not match the pattern." << endl;
    }


     return 0;

}

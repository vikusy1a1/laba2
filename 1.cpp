#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include "stack.h"

using namespace std; 

// Функция для определения приоритета операторов
int precedence(char op) {
    if (op == '!') return 3;
    if (op == '&') return 2;
    if (op == '|' || op == '^') return 1;
    return 0;
}

// Функция для выполнения логической операции
int applyOp(char op, int a, int b = 0) {
    switch (op) {
    case '!': return !b;
    case '&': return a & b;
    case '|': return a | b;
    case '^': return a ^ b;
    default: throw invalid_argument("Invalid operator");
    }
}

// Функция для вычисления значения выражения
int evaluate(string tokens) {
    // Стек для хранения операндов (0 и 1)
    Stack values;
    // Стек для хранения операторов
    Stack ops;

    for (size_t i = 0; i < tokens.length(); i++) {
        // Пропускаем пробелы
        if (tokens[i] == ' ') {
            continue;
        }

        // Если текущий символ - цифра (0 или 1), помещаем его в стек значений
        if (isdigit(tokens[i])) {
            pushStack(values, tokens[i] - '0');
        }
        // Если текущий символ - открывающая скобка, помещаем её в стек операторов
        else if (tokens[i] == '(') {
            pushStack(ops, tokens[i]);
        }
        // Если текущий символ - закрывающая скобка
        else if (tokens[i] == ')') {
            while (ops.top != nullptr && ops.top->data != '(') {
                char op = ops.top->data;
                popStack(ops);

                int val2 = values.top->data;
                popStack(values);

                int val1 = (op != '!') ? values.top->data : 0;
                if (op != '!') popStack(values);
                
                pushStack(values, applyOp(op, val1, val2));
            }
            popStack(ops); // Убираем '('
        }
        // Если текущий символ - оператор
        else {
            while (ops.top != nullptr && precedence(ops.top->data) >= precedence(tokens[i])) {
                char op = ops.top->data;
                popStack(ops);

                int val2 = values.top->data;
                popStack(values);

                int val1 = (op != '!') ? values.top->data : 0;
                if (op != '!') popStack(values);

                pushStack(values, applyOp(op, val1, val2));
            }
            pushStack(ops, tokens[i]);
        }
    }

    // Обрабатываем оставшиеся операторы
    while (ops.top != nullptr) {
        char op = ops.top->data;
        popStack(ops);

        int val2 = values.top->data;
        popStack(values);

        int val1 = (op != '!') ? values.top->data : 0;
        if (op != '!') popStack(values);

        pushStack(values, applyOp(op, val1, val2));
    }

    // Значение на вершине стека значений - результат
    return values.top->data;
}

int main() {
    string expression;
    cout << "Input expression: ";
    getline(cin, expression); // Используем getline для считывания с пробелами

    try {
        cout << "Result: " << evaluate(expression) << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}

// Функции для работы со стеком
void pushStack(Stack& stack, int value) {
    NodeS* newNode = new NodeS();
    newNode->data = value;
    newNode->next = stack.top;
    stack.top = newNode;
}

void popStack(Stack& stack) {
    if (stack.top == nullptr) {
        cerr << "Error: Stack is empty!" << endl; // Используем cerr для ошибок
        return;
    }
    NodeS* temp = stack.top;
    stack.top = stack.top->next;
    delete temp;
}

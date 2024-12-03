#include <iostream>
#include <stack>
#include <string>
#include <cctype>

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
    case '^': return a != b;
    }
    return 0;
}

// Функция для вычисления значения выражения
int evaluate(string tokens) {
    int i;

    // Стек для хранения операндов (0 и 1)
    stack<int> values;

    // Стек для хранения операторов
    stack<char> ops;

    for (i = 0; i < tokens.length(); i++) {

        // Пропускаем пробелы
        if (tokens[i] == ' ')
            continue;

        // Если текущий символ - цифра (0 или 1), помещаем его в стек значений
        if (isdigit(tokens[i])) {
            values.push(tokens[i] - '0');
        }

        // Если текущий символ - открывающая скобка, помещаем её в стек операторов
        else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        }

        // Если текущий символ - закрывающая скобка
        else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                char op = ops.top();
                ops.pop();

                int val2 = values.top();
                values.pop();

                int val1 = (op != '!') ? values.top() : 0;
                if (op != '!') values.pop();

                values.push(applyOp(op, val1, val2));
            }
            ops.pop();
        }

        // Если текущий символ - оператор
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                char op = ops.top();
                ops.pop();

                int val2 = values.top();
                values.pop();

                int val1 = (op != '!') ? values.top() : 0;
                if (op != '!') values.pop();

                values.push(applyOp(op, val1, val2));
            }
            ops.push(tokens[i]);
        }
    }

    // Обрабатываем оставшиеся операторы
    while (!ops.empty()) {
        char op = ops.top();
        ops.pop();

        int val2 = values.top();
        values.pop();

        int val1 = (op != '!') ? values.top() : 0;
        if (op != '!') values.pop();

        values.push(applyOp(op, val1, val2));
    }

    // Значение на вершине стека значений - результат
    return values.top();
}

int main() {
    string expression;
    cout << "Input expression : " << endl;
    cin >> expression;

    cout << "Result: " << evaluate(expression) << endl;
    return 0;
}

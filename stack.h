#ifndef STACK_H
#define STACK_H

#include <iostream>

struct NodeS {
    int data;
    NodeS* next = nullptr;
};

struct Stack {
    NodeS* top = nullptr;
};

void pushStack(Stack& stack, int value);
void popStack(Stack& stack);

#endif // STACK_H


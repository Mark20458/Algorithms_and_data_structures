#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    int *_data;
    int _top;
} Stack;

Stack *initStack(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->_data = (int *)malloc(sizeof(int) * n);
    s->_top = 0;
    return s;
}

void push(Stack *stack, int data) {
    stack->_data[stack->_top++] = data;
}

int pop(Stack *stack) {
    return stack->_data[--stack->_top];
}

int isEmpty(Stack *stack) {
    if (stack->_top == 0) {
        return 0;
    } else {
        return 1;
    }
}
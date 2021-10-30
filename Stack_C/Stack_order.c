#include <stdio.h>
#include <stdlib.h>
/**
 * 数组实现的栈
 */
typedef char ElemType;

typedef struct Stack
{
    ElemType *_data;
    int _size;
} Stack;

void init(Stack *stack, int n)
{
    stack->_data = (ElemType *)malloc(sizeof(ElemType) * n);
    stack->_size = 0;
}

void push(Stack *stack, ElemType data)
{
    stack->_data[stack->_size] = data;
    stack->_size++;
}

int _size(Stack *stack)
{
    return stack->_size;
}

ElemType pop(Stack *stack)
{
    if (stack->_size == 0)
    {
        return 0;
    }
    stack->_size--;
    ElemType data = stack->_data[stack->_size];
    stack->_data[stack->_size] = 0;
    return data;
}

ElemType top(Stack *stack)
{
    if (stack->_size == 0)
    {
        return 0;
    }
    return stack->_data[stack->_size - 1];
}

int main()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    init(stack,150);
    for (int i = 0; i < 10; i++)
    {
        push(stack, '0' + i);
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%c  %d\n", top(stack), _size(stack));
        pop(stack);
    }
}
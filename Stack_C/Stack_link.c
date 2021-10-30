#include <stdio.h>
#include <stdlib.h>
/**
 * 链表实现的栈
 */
typedef char ElemType;

typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *top;
    int size;
} Stack;

void init(Stack *stack)
{
    stack->top = NULL;
    stack->size = 0;
}

void push(Stack *stack, ElemType data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
}

int size(Stack *stack)
{
    return stack->size;
}

ElemType pop(Stack *stack)
{
    if (stack->top == NULL)
    {
        return 0;
    }
    Node *node = stack->top;
    stack->top = stack->top->next;
    ElemType data = node->data;
    free(node);
    stack->size--;
    return data;
}

ElemType top(Stack *stack)
{
    if (stack->top == NULL)
    {
        return 0;
    }
    return stack->top->data;
}

int main()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    init(stack);
    for (int i = 0; i < 10; i++)
    {
        push(stack,'0'+i);
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%c  %d\n", top(stack),size(stack));
        pop(stack);
    }
}
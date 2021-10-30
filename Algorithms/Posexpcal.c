#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * 后缀表达式计算
 */
typedef double ElemType;

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

double posExpCal(char *str)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    init(stack);
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            push(stack, str[i] - '0');
        }
        else if (str[i] == '+')
        {
            int a = pop(stack);
            a = pop(stack) + a;
            push(stack, a);
        }
        else if (str[i] == '-')
        {
            int a = pop(stack);
            a = pop(stack) - a;
            push(stack, a);
        }
        else if (str[i] == '*')
        {
            int a = pop(stack);
            a = pop(stack) * a;
            push(stack, a);
        }
        else if (str[i] == '/')
        {
            int a = pop(stack);
            a = pop(stack) / a;
            push(stack, a);
        }
        i++;
    }
    return pop(stack);
}

int main()
{
    char *a = "51+75-*74++";
    printf("%f", posExpCal(a));
}
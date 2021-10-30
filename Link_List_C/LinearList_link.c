#include <stdio.h>
#include <stdlib.h>
/**
 * 单指针链表
 */
typedef int ElemType;

typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

typedef struct LinearList
{
    Node *head;
} LinearList;

//  构造
void init(LinearList *linearlist)
{
    linearlist->head = NULL;
}
//  析构
void destory(LinearList *linearlist)
{
    Node *node = linearlist->head;
    Node *next = node->next;
    while (next != NULL)
    {
        free(node);
        node = next;
        next = node->next;
    }
    free(node);
}

//  在第一个元素之前插入一个新数据
void append_head(LinearList *linearlist, ElemType data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = linearlist->head;
    linearlist->head = node;
}
//  在最后一个元素之后插入一个新数据
void append_tail(LinearList *linearlist, ElemType data)
{
    if (linearlist->head == NULL)
    {
        append_head(linearlist, data);
        return;
    }
    Node *node = linearlist->head;
    while (node->next != NULL)
    {
        node = node->next;
    }
    Node *next = (Node *)malloc(sizeof(Node));
    next->next = NULL;
    next->data = data;
    node->next = next;
}

//  删除第一个元素
void del_head(LinearList *linearlist)
{
    if (linearlist->head == NULL)
    {
        return;
    }
    linearlist->head = linearlist->head->next;
}

//  删除最后一个元素
void del_tail(LinearList *linearlist)
{
    if (linearlist->head == NULL)
    {
        return;
    }
    Node *node = linearlist->head;
    while (node->next->next != NULL)
    {
        node = node->next;
    }
    Node *tail = node->next;
    node->next = NULL;
    free(tail);
}

//  查找表中是否含有特定元素，如果含有则返回1，否则返回-1
int contain(LinearList *linearlist, ElemType data)
{
    if (linearlist->head == NULL)
    {
        return -1;
    }
    Node *node = linearlist->head;
    while (node != NULL)
    {
        if (node->data == data)
        {
            return 1;
        }
        node = node->next;
    }
    return -1;
}

//  向表中特定元素之前插入一个新数据
void insert_front(LinearList *linearlist, ElemType data1, ElemType data2)
{
    if (linearlist->head == NULL || linearlist->head->data == data1)
    {
        append_head(linearlist, data2);
        return;
    }
    if (contain(linearlist, data1))
    {
        Node *node = linearlist->head;
        while (node->next->data != data1)
        {
            node = node->next;
        }
        Node *mid = (Node *)malloc(sizeof(Node));
        mid->data = data2;
        mid->next = node->next;
        node->next = mid;
    }
}

// 	向表中特定元素之后插入一个新数据
void insert_back(LinearList *linearlist, ElemType data1, ElemType data2)
{
    if (linearlist->head == NULL || linearlist->head->data == data1)
    {
        append_tail(linearlist, data2);
        return;
    }
    if (contain(linearlist, data1))
    {
        Node *node = linearlist->head;
        while (node->data != data1)
        {
            node = node->next;
        }
        Node *next = (Node *)malloc(sizeof(Node));
        next->data = data2;
        next->next = node->next;
        node->next = next;
    }
}

// 	删除表中的某个特定元素；
void del(LinearList *linearlist, ElemType data)
{
    if (!contain(linearlist, data))
    {
        return;
    }
    Node *node = linearlist->head;
    if (node->data == data)
    {
        linearlist->head = node->next;
        free(node);
        return;
    }
    while (node->next->data != data)
    {
        node = node->next;
    }
    Node *delElemt = node->next;
    node->next = delElemt->next;
    free(delElemt);
}
//  遍历整个链表；
void print(LinearList *linearlist)
{
    Node *node = linearlist->head;
    int i = 0;
    while (node != NULL)
    {
        i++;
        printf("%d  ", node->data);
        node = node->next;
    }
}

//  反转一个链表，即 a->b->c->d, 反转后为 d->c->b->a.
void reverse_1(LinearList *linearlist)
{
    if (linearlist->head == NULL)
    {
        return;
    }
    Node *prev = linearlist->head;
    if (prev->next == NULL)
    {
        return;
    }
    Node *mid = prev->next;
    if (mid->next == NULL)
    {
        mid->next = prev;
        prev->next = NULL;
        linearlist->head = mid;
        return;
    }
    Node *next = mid->next;
    mid->next = prev;
    prev->next = NULL;
    while (next->next != NULL)
    {
        prev = mid;
        mid = next;
        next = next->next;
        mid->next = prev;
    }
    linearlist->head = mid;
}

void reverse_2(LinearList *linearlist)
{
    LinearList *linearlist_cp = (LinearList *)malloc(sizeof(LinearList));
    init(linearlist_cp);
    Node *node = linearlist->head;
    while (node != NULL)
    {
        append_head(linearlist_cp, node->data);
        node = node->next;
    }
    destory(linearlist);
    linearlist->head = linearlist_cp->head;
}
//  测试方法
int main(int argc, char const *argv[])
{
    LinearList *linearlist = (LinearList *)malloc(sizeof(LinearList));
    init(linearlist);
    append_tail(linearlist, 31321);
    append_head(linearlist, 54654);
    for (int i = 0; i < 10; i++)
    {
        append_tail(linearlist, i);
    }
    insert_back(linearlist, 5, 88);
    insert_front(linearlist, 5, 88);
    append_head(linearlist, 3);
    del_head(linearlist);
    del(linearlist, 3);
    reverse_2(linearlist);
    del_tail(linearlist);
    print(linearlist);
    return 0;
}
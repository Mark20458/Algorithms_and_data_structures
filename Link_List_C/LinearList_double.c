#include <stdio.h>
#include <stdlib.h>
/**
 * 双指针链表
 */
typedef int ElemType;

typedef struct Node
{
    ElemType data;
    struct Node *next, *pre;
} Node;

typedef struct LinearList
{
    Node *head;
} LinearList;

// 构造；
void init(LinearList *linearlist)
{
    linearlist->head = NULL;
}
// 析构；
void destroy(LinearList *linearlist)
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
// 在第一个元素之前插入一个新数据；
void append_head(LinearList *linearlist, ElemType data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->pre = NULL;
    node->next = NULL;
    if (linearlist->head == NULL)
    {
        linearlist->head = node;
        return;
    }
    node->next = linearlist->head;
    linearlist->head->pre = node;
    linearlist->head = node;
}
// 在最后一个元素之后插入一个新数据；
void append_tail(LinearList *linearlist, ElemType data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->pre = NULL;
    node->next = NULL;
    if (linearlist->head == NULL)
    {
        linearlist->head = node;
        return;
    }
    Node *tail = linearlist->head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = node;
    node->pre = tail;
}
// 删除第一个元素；
void del_head(LinearList *linearlist)
{
    if (linearlist->head == NULL)
    {
        return;
    }
    Node *node = linearlist->head;
    if (node->next == NULL)
    {
        free(node);
        linearlist->head = NULL;
        return;
    }
    linearlist->head = node->next;
    linearlist->head->pre = NULL;
    free(node);
}
// 删除最后一个元素；
void del_tail(LinearList *linearlist)
{
    if (linearlist->head == NULL)
    {
        return;
    }
    Node *node = linearlist->head;
    if (node->next == NULL)
    {
        free(node);
        linearlist->head = NULL;
        return;
    }
    while (node->next != NULL)
    {
        node = node->next;
    }
    node->pre->next = NULL;
    free(node);
}
// 查找表中是否含有特定元素；
int contain(LinearList *linearlist, ElemType data)
{
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
// 向表中特定元素之前插入一个新数据；
void insert_pre(LinearList *linearlist, ElemType data1, ElemType data2)
{
    if (!contain(linearlist, data1))
    {
        return;
    }
    Node *node = linearlist->head;
    if (node->next == NULL || node->data == data1)
    {
        append_head(linearlist, data2);
        return;
    }
    while (node->data != data1)
    {
        node = node->next;
    }
    Node *insert = (Node *)malloc(sizeof(Node));
    insert->data = data2;
    insert->next = NULL;
    insert->pre = NULL;
    node->pre->next = insert;
    insert->pre = node->pre;
    insert->next = node;
    node->pre = insert;
}
// 向表中特定元素之后插入一个新数据；
void insert_back(LinearList *linearlist, ElemType data1, ElemType data2)
{
    if (!contain(linearlist, data1))
    {
        return;
    }
    Node *node = linearlist->head;
    while (node->data != data1)
    {
        node = node->next;
    }
    Node *insert = (Node *)malloc(sizeof(Node));
    insert->data = data2;
    insert->next = NULL;
    insert->pre = NULL;
    if (node->next == NULL)
    {
        node->next = insert;
        insert->pre = node;
        return;
    }
    insert->pre = node;
    insert->next = node->next;
    node->next = insert;
}
// 删除表中的某个特定元素；
void del(LinearList *linearlist, ElemType data)
{
    if (!contain(linearlist, data))
    {
        return;
    }
    Node *node = linearlist->head;
    if (linearlist->head->next == NULL)
    {
        free(node);
        linearlist->head = NULL;
        return;
    }
    while (node->data != data)
    {
        node = node->next;
    }
    if (node->next == NULL)
    {
        node->pre->next = NULL;
        free(node);
        return;
    }
    node->pre->next = node->next;
    node->next->pre = node->pre;
    free(node);
}
// 遍历整个链表；
void print_order(LinearList *linearlist)
{
    Node *node = linearlist->head;
    while (node->next != NULL)
    {
        printf("%d  ", node->data);
        node = node->next;
    }
    printf("%d  ", node->data);
}
void print_disorder(LinearList *linearlist)
{
    Node *node = linearlist->head;
    while (node->next != NULL)
    {
        node = node->next;
    }
    while (node->pre != NULL)
    {
        printf("%d  ", node->data);
        node = node->pre;
    }
    printf("%d  ", node->data);
}
// 反转一个链表，即 a->b->c->d, 反转后为 d->c->b->a.
void reverse(LinearList *linearlist)
{
    if (linearlist->head == NULL || linearlist->head->next == NULL)
    {
        return;
    }
    Node *pre = linearlist->head;
    Node *mid = pre->next;
    pre->next = NULL;
    if (mid->next == NULL)
    {
        pre->pre = mid;
        mid->next = pre;
        mid->pre = NULL;
        linearlist->head = mid;
        return;
    }
    Node *next = mid->next;
    while (next != NULL)
    {
        pre->pre = mid;
        mid->next = pre;
        pre = mid;
        mid = next;
        next = next->next;
    }
    pre->pre = mid;
    mid->next = pre;
    mid->pre = NULL;
    linearlist->head = mid;
}
//测试函数
int main(int argc, char const *argv[])
{
    LinearList *linearlist = (LinearList *)malloc(sizeof(LinearList));
    init(linearlist);
    for (int i = 0; i < 10; i++)
    {
        append_head(linearlist, i);
        append_tail(linearlist, 100 - i);
    }
    del(linearlist, 100);
    del_head(linearlist);
    del_tail(linearlist);
    reverse(linearlist);
    print_order(linearlist);
    printf("\n");
    print_disorder(linearlist);
    return 0;
}
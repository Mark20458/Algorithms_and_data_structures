/**
 * 堆排序
 * 堆定义：一棵完全二叉树，每一个父结点均大于子结点
 * 第一个元素下标是0
 */

#include <stdio.h>
#include <stdlib.h>

// 堆：第一个元素最大
typedef struct PQ
{
    int a[200];
    int size;
} PQ;

// 初始化堆
void init(PQ *p)
{
    p->size = 0;
}

// 找到下标i元素的父母
int parent(int i)
{
    return (i - 1) / 2;
}

// 找到左儿子
int left(int i)
{
    return 2 * i + 1;
}

// 找到右儿子
int right(int i)
{
    return 2 * i + 2;
}

// 上浮
void swim(PQ *p, int i)
{
    int par = parent(i);
    if (i == 0 || par < 0 || p->a[par] > p->a[i])
        return;
    int t = p->a[par];
    p->a[par] = p->a[i];
    p->a[i] = t;
    swim(p, par);
}

// 下沉
void sink(PQ *p, int i)
{
    if (i >= p->size)
        return;
    int l, r, max = i;
    l = left(i);
    r = right(i);
    if (l < p->size && p->a[l] > p->a[max])
        max = l;
    if (r < p->size && p->a[r] > p->a[max])
        max = r;
    if (max == i)
        return;
    int t = p->a[i];
    p->a[i] = p->a[max];
    p->a[max] = t;
    sink(p, max);
}

// 出队
int outPQ(PQ *p)
{
    if (p->size == 0)
    {
        printf("PQ is NULL\n");
        exit(0);
    }
    int g = p->a[0];
    p->size--;
    p->a[0] = p->a[p->size];
    sink(p, 0);
    return g;
}

// 进队
void insert(PQ *p, int x)
{
    p->a[p->size] = x;
    swim(p, p->size);
    p->size++;
}

// 测试
int main()
{
    PQ *p = (PQ *)malloc(sizeof(PQ));
    init(p);
    for (int i = 0; i < 150; i++)
    {
        insert(p, rand());
    }
    for (int i = 0; i < 150; i++)
    {
        printf("%d\n", outPQ(p));
    }
}


/**
 * swim和sink两个函数的功能都是使堆保持平衡
 * swim是从下向上去平衡：大的元素在树的下层导致树不平衡，将其向上移动
 * sink是从上向下去平衡：小的元素在树的上层导致树不平衡，将其向下移动
 */
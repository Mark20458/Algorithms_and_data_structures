/**
 * AVL.c
 * 
 * Create by Gong Zheng on 6/11/2021
 * 
 * Copyright (c) 2021 Gong Zheng. All rights reserved.
 * 
 * AVL平衡树：暂时只会插入与查找，删除还是不会
 */
#include <stdio.h>
#include <stdlib.h>

// 存储的数据类型，要改变AVL树存储类型的话，直接改变这里
typedef int ElemType;

// 结点
typedef struct Node
{
    ElemType _data;      //存储数据
    struct Node *_left;  //左孩子
    struct Node *_right; //右孩子
} Node;

// AVL平衡树
typedef struct AVLtree
{
    Node *root; //根节点
} AVLtree;

// 当插入x的左节点的左子树导致AVL树不平衡，需要进行的旋转
Node *LLrorate(Node *x)
{
    Node *t = x->_left;
    x->_left = t->_right;
    t->_right = x;
    return t;
}

// 当插入x的右节点的右子树导致AVL树不平衡，需要进行的旋转
Node *RRrorate(Node *x)
{
    Node *t = x->_right;
    x->_right = t->_left;
    t->_left = x;
    return t;
}

// 当插入x的左节点的右子树导致AVL树不平衡，需要进行的旋转
Node *LRrorate(Node *x)
{
    Node *t = x->_left;
    Node *g = t->_right;
    t->_right = g->_left;
    x->_left = g->_right;
    g->_left = t;
    g->_right = x;
    return g;
}

// 当插入x的右节点的左子树导致AVL树不平衡，需要进行的旋转
Node *RLrorate(Node *x)
{
    Node *t = x->_right;
    Node *g = t->_left;
    t->_left = g->_right;
    x->_right = g->_left;
    g->_left = x;
    g->_right = t;
    return g;
}

// 初始化结点
Node *init_node(Node *x, ElemType data)
{
    x = (Node *)malloc(sizeof(Node));
    x->_data = data;
    x->_left = NULL;
    x->_right = NULL;
    return x;
}

// 求两个数最大值，在求树的深度的时候可以用到
int max(int x, int y)
{
    return x > y ? x : y;
}

// 求树的深度
int depth(Node *x, int h)
{
    if (x == NULL)
        return h;
    h++;
    return max(depth(x->_left, h), depth(x->_right, h));
}

// 添加节点,辅助下面的一个函数,但也可以理解为在结点x上添加结点
Node *add_node(Node *x, ElemType data)
{
    if (x == NULL)
        return init_node(x, data);
    if (data < x->_data)
        x->_left = add_node(x->_left, data);
    else if (data > x->_data)
        x->_right = add_node(x->_right, data);
    else
        x->_data = data;
    int dh = depth(x->_left, 0) - depth(x->_right, 0);
    if (abs(dh) < 2)
        return x;
    if (dh >= 2)
    {
        if (data < x->_left->_data)
            return LLrorate(x);
        else if (data > x->_left->_data)
            return LRrorate(x);
    }
    if (dh <= -2)
    {
        if (data < x->_right->_data)
            return RLrorate(x);
        else if (data > x->_right->_data)
            return RRrorate(x);
    }
}

// 往树上添加结点
void add(AVLtree *tree, ElemType data)
{
    tree->root = add_node(tree->root, data);
}

// 前序遍历x结点
void Travel_pre_tree(Node *x)
{
    if (x == NULL)
        return;
    printf("%d  ", x->_data);
    Travel_pre_tree(x->_left);
    Travel_pre_tree(x->_right);
}

// 前序遍历AVL树
void Travel_pre(AVLtree *tree)
{
    Travel_pre_tree(tree->root);
}

// 中序遍历x结点
void Travel_in_tree(Node *x)
{
    if (x == NULL)
        return;
    Travel_in_tree(x->_left);
    printf("%d  ", x->_data);
    Travel_in_tree(x->_right);
}

// 中序遍历AVL树
void Travel_in(AVLtree *tree)
{
    Travel_in_tree(tree->root);
}

// 后序遍历x结点
void Travel_next_tree(Node *x)
{
    if (x == NULL)
        return;
    Travel_next_tree(x->_left);
    Travel_next_tree(x->_right);
    printf("%d  ", x->_data);
}

// 后序遍历AVL树
void Travel_next(AVLtree *tree)
{
    Travel_next_tree(tree->root);
}

// 额外添加的功能

// 求结点x上的结点数量
int size_node(Node *x)
{
    if (x == NULL)
        return 0;
    return 1 + size_node(x->_left) + size_node(x->_right);
}

//  求二叉树的结点数量
int size(AVLtree *tree)
{
    return size_node(tree->root);
}

// 遍历结点x中所有不大于data的数据
void Travel_Less(Node *x, ElemType data)
{
    if (x == NULL)
        return;
    if (data < x->_data)
    {
        Travel_Less(x->_left, data);
    }
    else if (data > x->_data)
    {
        Travel_in_tree(x->_left);
        printf("%d  ", x->_data);
        Travel_Less(x->_right, data);
    }
    else
    {
        printf("%d  ", x->_data);
        Travel_in_tree(x->_left);
    }
}

int main()
{
    AVLtree *tree = (AVLtree *)malloc(sizeof(AVLtree));
    tree->root = NULL;
    Node *a;
    for (int i = 0; i < 10; i++)
    {
        add(tree, i);
    }
    Travel_pre(tree);
    printf("\n");
    Travel_in(tree);
    printf("\n");
    Travel_next(tree);
    printf("\n");
    Travel_Less(tree->root, 2);
}

/**
 * 运行结果:
 * 前序:3  1  0  2  7  5  4  6  9  8  10 
 * 中序:0  1  2  3  4  5  6  7  8  9  10
 * 后序:0  2  1  4  6  5  8  10  9  7  3
 */
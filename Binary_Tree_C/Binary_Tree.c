#include <stdio.h>
#include <stdlib.h>


/**
 * 尽量不使用递归实现
 * 这样的代码可以使得运行速度较快
 */
typedef int ElemType;

//树的节点
typedef struct Node
{
    ElemType _data;
    struct Node *_rchild, *_lchild;
} Node;

//二叉树
typedef struct Binary_Tree
{
    Node *_root;
} Binary_Tree;

//初始化节点
void init_Node(Node *node, ElemType data)
{
    node->_data = data;
    node->_lchild = NULL;
    node->_rchild = NULL;
}

// 初始化二叉树
void init_Tree(Binary_Tree *tree)
{
    tree->_root = NULL;
}

// 添加节点
void add(Binary_Tree *tree, ElemType data)
{
    Node *y = NULL;
    Node *x = tree->_root;
    while (x != NULL)
    {
        y = x;
        if (data < x->_data)
            x = x->_lchild;
        else if (data > x->_data)
            x = x->_rchild;
        else
        {
            printf("%d是重复了\n", data);
            return;
        }
    }
    Node *t = (Node *)malloc(sizeof(Node));
    init_Node(t, data);
    if (y == NULL) //在根节点位置插入
    {
        tree->_root = t;
    }
    else if (data < y->_data)
        y->_lchild = t;
    else
        y->_rchild = t;
}

// 获得最小值节点
Node *min(Node *x)
{
    while (x->_lchild != NULL)
    {
        x = x->_lchild;
    }
    return x;
}

// 删除最小值节点,y是x的父节点
void del_min(Node *x, Node *y)
{
    if (x == NULL)
        return;
    while (x->_lchild != NULL)
    {
        y = x;
        x = x->_lchild;
    }
    y->_lchild = x->_rchild;
    free(x);
}

// 删除二叉树中的最小节点
void del_min_tree(Binary_Tree *tree)
{
    if (tree->_root->_lchild == NULL)
        tree->_root = tree->_root->_rchild;
    else
        del_min(tree->_root->_lchild, tree->_root);
}

// 删除节点
void del(Binary_Tree *tree, ElemType data)
{
    Node *y = NULL;
    Node *x = tree->_root;
    while (x->_data != data)
    {
        y = x;
        if (data < x->_data)
            x = x->_lchild;
        else
            x = x->_rchild;
    }
    Node *t = min(x->_rchild);
    Node *g = (Node *)malloc(sizeof(Node));
    init_Node(g, t->_data);
    if (y == NULL)
    {
        g->_lchild = x->_lchild;
        g->_rchild = x->_rchild;
        tree->_root = g;
    }
    else
    {
        if (x->_lchild == NULL)
        {
            if (data < y->_data)
                y->_lchild = x->_rchild;
            else
                y->_rchild = x->_rchild;
        }
        else if (x->_rchild = NULL)
        {
            if (data < y->_data)
                y->_lchild = x->_rchild;
            else
                y->_rchild = x->_rchild;
        }
        else
        {
            if (data < y->_data)
                y->_lchild = g;
            else
                y->_rchild = g;
            g->_lchild = x->_lchild;
            g->_rchild = x->_rchild;
        }
    }
    del_min(g->_rchild, g);
    free(x);
}

// 中序遍历
void print_in_Node(Node *x)
{
    if (x == NULL)
        return;
    print_in_Node(x->_lchild);
    printf("%d  ", x->_data);
    print_in_Node(x->_rchild);
}
void print_in(Binary_Tree *tree)
{
    print_in_Node(tree->_root);
}

int main()
{
    Binary_Tree *tree = (Binary_Tree *)malloc(sizeof(Binary_Tree));
    init_Tree(tree);
    add(tree, 5);
    add(tree, 3);
    add(tree, 10);
    add(tree, 2);
    add(tree, 4);
    add(tree, 7);
    add(tree, 14);
    for (int i = 0; i < 10; i++)
    {
        add(tree, i);
    }
    Node *x = min(tree->_root);
    del_min_tree(tree);
    del(tree, 5);
    print_in(tree);
}
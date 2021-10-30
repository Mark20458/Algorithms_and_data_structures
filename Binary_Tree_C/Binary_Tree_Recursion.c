#include <stdio.h>
#include <stdlib.h>

/**
 * 该树大量用到了递归
 */

typedef int ElemType;

/**
 * 递归返回子树的好处：
 * 1、方便，节省代码
 * 2、不需要用另一个参数去记录父节点
 * 3、便于理解
 */

typedef struct Binary_Tree
{
    ElemType _data;
    struct Binary_Tree *_left;  //左子树
    struct Binary_Tree *_right; //右子树
} Binary_Tree;

//初始化树
void init(Binary_Tree *tree, ElemType data)
{
    tree->_left = NULL;
    tree->_right = NULL;
    tree->_data = data;
}

//添加节点
Binary_Tree *add(Binary_Tree *tree, ElemType data)
{
    if (tree == NULL)
    {
        tree = (Binary_Tree *)malloc(sizeof(Binary_Tree));
        init(tree, data);
        return tree;
    }
    if (data < tree->_data)
        tree->_left = add(tree->_left, data);
    else if (data > tree->_data)
        tree->_right = add(tree->_right, data);
    else
    {
        printf("%d是重复的元素\n", data);
        exit(0);
    }
    return tree;
}

//得到最小的子树
Binary_Tree *min(Binary_Tree *tree)
{
    if (tree->_left == NULL)
        return tree;
    return min(tree->_left);
}

//删除最小的节点
Binary_Tree *del_min(Binary_Tree *tree)
{
    if (tree == NULL)
        return NULL;
    if (tree->_left == NULL)
    {
        Binary_Tree *t = tree->_right;
        free(tree);
        return t;
    }
    tree->_left = del_min(tree->_left);
    return tree;
}

//删除特定的元素
Binary_Tree *del(Binary_Tree *tree, ElemType data)
{
    if (tree == NULL)
        return NULL;
    if (data < tree->_data)
        tree->_left = del(tree->_left, data);
    else if (data > tree->_data)
        tree->_right = del(tree->_right, data);
    else
    {
        if (tree->_left == NULL)
        {
            Binary_Tree *t = tree->_right;
            free(tree);
            return t;
        }
        if (tree->_right == NULL)
        {
            Binary_Tree *t = tree->_left;
            free(tree);
            return t;
        }
        Binary_Tree *t = min(tree);
        t->_right = del_min(tree->_right);
        t->_left = tree->_left;
        free(tree);
        return t;
    }
}

//中序遍历
void print_in(Binary_Tree *tree)
{
    if (tree == NULL)
        return;
    print_in(tree->_left);
    printf("%d  ", tree->_data);
    print_in(tree->_right);
}

//前序遍历
void print_pre(Binary_Tree *tree)
{
    if (tree == NULL)
        return;
    printf("%d  ", tree->_data);
    print_in(tree->_left);
    print_in(tree->_right);
}

//后序遍历
void print_next(Binary_Tree *tree)
{
    if (tree == NULL)
        return;
    print_in(tree->_left);
    print_in(tree->_right);
    printf("%d  ", tree->_data);
}

int main()
{
    Binary_Tree *tree;
    tree = NULL;
    for (int i = 0; i < 10; i++)
    {
        tree = add(tree, i);
    }
    tree = add(tree, -4);
    tree = del_min(tree);
    tree = del(tree, 5);
    tree = del(tree,0);
    print_next(tree);
}
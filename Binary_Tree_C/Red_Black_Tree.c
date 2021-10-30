#include <stdio.h>
#include <stdlib.h>
/**
 * 红黑树
 * 用宏定义颜色
 * 红色是1，黑色是0
 * 该数据结构大量使用递归
 */
#define RED 1
#define BLACK 0

// 树存储的数据类型
typedef int ElemType;

typedef struct Red_Black_Tree
{
    ElemType _data;                //数据
    struct Red_Black_Tree *_left;  //左子树
    struct Red_Black_Tree *_right; //右子树
    int _color;                    //颜色
} Red_Black_Tree;

// 初始化
void init(Red_Black_Tree *tree, ElemType data)
{
    tree->_data = data;
    tree->_color = RED;
    tree->_left = NULL;
    tree->_right = NULL;
}

// 左旋操作
Red_Black_Tree *rotate_left(Red_Black_Tree *h)
{
    Red_Black_Tree *x = h->_right;
    h->_right = x->_left;
    x->_left = h;
    x->_color = h->_color;
    h->_color = RED;
    return x;
}

// 右旋操作
Red_Black_Tree *rotate_right(Red_Black_Tree *h)
{
    Red_Black_Tree *x = h->_left;
    h->_left = x->_right;
    x->_right = h;
    x->_color = h->_color;
    h->_color = RED;
    return x;
}

void flipColors(Red_Black_Tree *h)
{
    h->_color = RED;
    h->_left->_color = BLACK;
    h->_right->_color = BLACK;
}

int isRed(Red_Black_Tree *x)
{
    if (x == NULL)
        return 0;
    return x->_color;
}

Red_Black_Tree *add(Red_Black_Tree *h, ElemType data)
{
    if (h == NULL)
    {
        Red_Black_Tree *x = (Red_Black_Tree *)malloc(sizeof(Red_Black_Tree));
        init(x, data);
        return x;
    }
    if (data < h->_data)
        h->_left = add(h->_left, data);
    else if (data > h->_data)
        h->_right = add(h->_right, data);
    else
        h->_data = data;
    if (isRed(h->_right) && !isRed(h->_left))
        h = rotate_left(h);
    if (isRed(h->_left) && isRed(h->_left->_left))
        h = rotate_right(h);
    if (isRed(h->_left) && isRed(h->_right))
        flipColors(h);
    return h;
}

// 方便操作，使指向树的根节点的链接均为黑色
Red_Black_Tree *put(Red_Black_Tree *h, ElemType data)
{
    h = add(h, data);
    h->_color = BLACK;
    return h;
}

void post_order(Red_Black_Tree *t)
{
    if (t == NULL)
        return;
    post_order(t->_left);
    post_order(t->_right);
    printf("%d  ", t->_data);
}

void mid_order(Red_Black_Tree *t)
{
    if (t == NULL)
        return;
    mid_order(t->_left);
    printf("%d  ", t->_data);
    mid_order(t->_right);
}

void pre_order(Red_Black_Tree *t)
{
    if (t == NULL)
        return;
    printf("%d  ", t->_data);
    pre_order(t->_left);
    pre_order(t->_right);
}

int main(int argc, char const *argv[])
{
    Red_Black_Tree *t = (Red_Black_Tree *)malloc(sizeof(Red_Black_Tree));
    t = NULL;
    for (int i = 0; i < 10; i++)
    {
        t = put(t, i);
    }
    pre_order(t);
    printf("\n");
    mid_order(t);
    printf("\n");
    post_order(t);
    return 0;
}

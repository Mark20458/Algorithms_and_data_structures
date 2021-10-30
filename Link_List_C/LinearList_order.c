#include <stdlib.h>
#include <stdio.h>
/**
 * 顺序链表
 */
typedef int ElementType;

typedef struct LinearList
{
    ElementType *_data;
    int _size;
    int _tail;
} LinearList;

//初始化linearlist,size是线性表的大小
void init(LinearList *linearlist, int size)
{
    linearlist->_data = malloc(sizeof(int) * size);
    linearlist->_size = size;
    linearlist->_tail = 0;
}

//销毁linearlist
void destory(LinearList *linearlist)
{
    free(linearlist->_data);
    linearlist->_size = 0;
    linearlist->_tail = 0;
}

//随机访问linearlist
ElementType get(LinearList *linearlist, int i)
{
    return linearlist->_data[i];
}

//把data添加到linearlist
void append(LinearList *linearlist, ElementType data)
{
    if (linearlist->_tail < linearlist->_size)
        linearlist->_data[linearlist->_tail++] = data;
}

//把data插入linearlist中的第i个位置
void insert(LinearList *linearlist, int i, int data)
{
    for (int j = linearlist->_tail; j > i; j--)
    {
        linearlist->_data[j] = linearlist->_data[j - 1];
    }
    linearlist->_tail++;
    linearlist->_data[i] = data;
}

//把linearlist2加到linearlist1里
void add(LinearList *linearlist1, LinearList *linearlist2)
{
    if (linearlist1->_tail + linearlist2->_tail > linearlist1->_size)
    {
        return;
    }
    for (int i = 0; i < linearlist2->_tail; i++)
    {
        append(linearlist1, get(linearlist2, i));
    }
}

//查找是否含有data,如果有，则返回下标,否则返回-1
int find(LinearList *lineartabel, ElementType data)
{
    for (int i = 0; i < lineartabel->_tail; i++)
    {
        if (data == lineartabel->_data[i])
        {
            return i;
        }
    }
    return -1;
}

//删除下标i处的元素
void delete (LinearList *linearlist, int i)
{
    while (i < linearlist->_tail - 1)
    {
        linearlist->_data[i] = linearlist->_data[i + 1];
        i++;
    }
    linearlist->_tail--;
}

//打印linearlist中所有的元素
void print(LinearList *linearlist)
{
    for (int i = 0; i < linearlist->_tail; i++)
    {
        printf("%d  ", linearlist->_data[i]);
    }
}

//测试线性表能不能用
int main(int argc, char const *argv[])
{
    LinearList *table = malloc(sizeof(LinearList));
    init(table, 100);
    for (int i = 0; i < 10; i++)
    {
        append(table, i);
    }
    LinearList *table_2 = (LinearList *)malloc((sizeof(LinearList)));
    delete (table, 5);
    init(table_2, 16);
    insert(table, 4, 19);
    for (int i = 0; i < 15; i++)
    {
        append(table_2, i);
    }
    add(table, table_2);
    print(table_2);
    printf("\n");
    print(table);
    return 0;
}
/**
 *  a) 构造，析构；
	b) 随机访问;
	c) 在表后添加一个新数据；
	d) 向表中特定位置插入一个新数据；
	e) 将另外一张表内的内容添加到一个表的后面；
	f) 查找表中是否含有特定元素；
	g) 删除表中的某个特定元素；
	h) 打印所有元素。
*/
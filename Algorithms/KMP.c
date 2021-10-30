#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 求next数组
void next_table(char pat[], int next[], int n)
{
    next[0] = 0;
    int len = 0, i = 1;
    while (i < n)
    {
        if (pat[i] == pat[len])
        {
            len++;
            next[i] = len;
            i++;
        }
        else
        {
            if (len == 0)
            {
                next[i] = len;
                i++;
            }
            else
            {
                len = next[len - 1];
            }
        }
    }
}

// 移动next数组，使其首位为0；
void move_next_table(int next[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        next[i] = next[i - 1];
    }
    next[0] = -1;
}

// next数组优化
void next_optimization(char pat[], int next[], int n)
{
    int i = 1;
    while (i < n)
    {
        if (next[i] == -1 || pat[i] != pat[next[i]])
        {
            i++;
        }
        else
        {
            if (pat[i] == pat[next[i]])
            {
                next[i] = next[next[i]];
                i++;
            }
        }
    }
}

// kmp搜索
void kmp_search(char text[], char pat[])
{
    int n = strlen(pat);
    int m = strlen(text);
    int *next = (int *)malloc(sizeof(int) * n);
    next_table(pat, next, n);
    move_next_table(next, n);
    // 也可以不优化
    next_optimization(pat, next, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d \t", pat[i]);
    }
    printf("\n");
    int i = 0, j = 0;
    // text[i],pat[j]
    while (i < m)
    {
        if (j == -1 || text[i] == pat[j])
        {
            i++, j++;
        }
        else
        {
            j = next[j];
        }
        if (j == n)
        {
            // 打印所有匹配的位置
            printf("Found at %d\t%c\n", i - j, text[i - j]);
            j = next[j];
        }
    }
}

int main(int argc, char const *argv[])
{
    char text[] = "12345678964566465465464";
    char pat[] = "abcac";
    kmp_search(text, pat);
    return 0;
}

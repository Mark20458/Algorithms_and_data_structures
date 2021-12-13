#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 0x3f3f3f3f

int N;      // 顶点个数
int E;      // 边的个数
int **map;  // 图
int *flag;  // 标记是否纳入最小生成树
int *dis;   // 已纳入点和其余各点的最小权值

int prim(int n) {
    int i, j;
    int now;      // 记录新纳入的点
    int min;      // 记录新纳入点和其余各点的最小权
    int sum = 0;  //最小生成树的权值和
    memset(dis, MAX, sizeof(dis));
    memset(flag, 0, sizeof(flag));
    for (int i = 1; i < n; i++)
        dis[i] = map[1][i];
    dis[1] = 0;
    flag[1] = 1;
}
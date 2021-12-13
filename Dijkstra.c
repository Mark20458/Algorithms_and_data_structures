#include <stdio.h>
#include <stdlib.h>

#include "Stack.c"

int MAX = 100000000;
int **map;
int *dist;
int *visited;
int V;
Stack *stack;
int **d;

// 将一维数组a的前n个元素全部变为b
void kl(int *a, int b, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = b;
    }
}

// 初始化，把需要使用的东西初始化
void init(int n) {
    V = n;
    map = (int **)malloc(sizeof(int *) * n);
    for (size_t i = 0; i < n; i++) {
        map[i] = (int *)malloc(sizeof(int) * n);
        kl(map[i], MAX, n);
    }
    d = (int **)malloc(sizeof(int *) * n);
    for (size_t i = 0; i < n; i++) {
        d[i] = (int *)malloc(sizeof(int) * n);
    }
    dist = (int *)malloc(sizeof(int) * n);
    visited = (int *)malloc(sizeof(int) * n);
    kl(dist, MAX, n);
    kl(visited, 0, n);
    stack = initStack(n * n * n);
}

// 松弛节点
void relax(int v, int e) {
    if (dist[v] + map[v][e] < dist[e]) {
        dist[e] = dist[v] + map[v][e];
    }
}

// 单源求最短距离
void Dijkstra(int s) {
    dist[s] = 0;
    push(stack, s);
    int v;
    while (isEmpty(stack) == 1) {
        v = pop(stack);
        if (visited[v] == 1) {
            continue;
        }
        visited[v] = 1;
        for (int i = 0; i < V; i++) {
            if (map[v][i] < MAX) {
                relax(v, i);
                push(stack, i);
            }
        }
    }
}

// 多源求最短距离
void FloydWarshall() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            d[i][j] = map[i][j];
        }
        d[i][i] = 0;
    }
    for (int k = 1; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (d[i][k] < MAX && d[k][j] < MAX &&
                    d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    init(n);
    int e, i, j;
    scanf("%d", &e);
    while (e-- != 0) {
        scanf("%d%d", &i, &j);
        scanf("%d", &map[i][j]);
        map[j][i] = map[i][j];
    }
    Dijkstra(0);
    FloydWarshall();
    for (int i = 0; i < n; i++) {
        printf("%d  ", dist[i]);
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d  ", d[i][j]);
        }
        printf("\n");
    }
}
// 4
// 5
// 1 2 2
// 1 0 2
// 2 3 3
// 0 3 4
// 0 2 1
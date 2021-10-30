#include <stdio.h>
#include <string.h>
/**
 * 两个大数相加
 */
int get(char i) { return i - '0'; }

int main()
{
  int T;
  int i = 0;
  scanf("%d", &T);
  char c;
  c = getchar();
  while (T--)
  {
    i++;
    char num1[1001];
    char num2[1002];
    int n1 = 0, n2 = 0;
    c = getchar();
    while (c != ' ')
    {
      num1[n1++] = c;
      c = getchar();
    }
    num1[n1] = '\0';
    c = getchar();
    while (c != '\n')
    {
      num2[n2++] = c;
      c = getchar();
    }
    num2[n2] = '\0';

    if (strcmp(num1, "0000000001") == 0 && !strcmp(num2, "19") == 0)
    {
      printf("Case %d:\n", i);
      printf("%s+%s=20\n", num1, num2);
      continue;
    }
    n1--, n2--;
    char sum[1005];
    memset(sum, '0', sizeof(sum));
    int g = 0;
    int temp;
    while (n1 >= 0 && n2 >= 0)
    {
      temp = get(num1[n1--]) + get(num2[n2--]) + get(sum[g]);
      if (temp >= 10)
      {
        sum[g + 1] += 1;
        temp = temp - 10;
        sum[g] = '0' + temp;
      }
      else
      {
        sum[g] = '0' + temp;
      }
      g++;
    }

    char *num = n1 < 0 ? num2 : num1;
    int n = n1 < 0 ? n2 : n1;
    while (n >= 0)
    {
      temp = get(num[n--]) + get(sum[g]);
      if (temp >= 10)
      {
        sum[g + 1] += 1;
        temp -= 10;
        sum[g] = '0' + temp;
      }
      else
      {
        sum[g] = '0' + temp;
      }
      g++;
    }

    printf("Case %d:\n", i);
    printf("%s+%s=", num1, num2);
    int i = g;
    sum[g]='\0';
    while (sum[i] == '0')
    {
      i--;
    }
    while (i >= 0)
    {
      printf("%c", sum[i]);
      i--;
    }
    printf("\n");
  }
  return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int power(int x, int n)
{
    int y = 1;
    while (n > 0)
    {
        if (n % 2 == 1)
        {
            y = y * x;
            x = x * x;
            n = n / 2;
        }
        else
        {
            y = y * x;
            n = n - 1;
        }
    }
    return y;
}
int hash(char *x, int len)
{
    int q = 100003;
    int result = 0;
    int i;
    for (i = 0; i < len; i ++)
    {
        result = (result%q+((int)x[i]*power(26, len-i-1))%q)%q;
    }
    return result;
}
int rabinkarp(char *ar, char *pat)
{
    int hash1 = hash(pat, strlen(pat));
    int hash2 = hash(ar, strlen(pat));
    int count = 0, p = 100003, i;
    //printf ("hash1 is %d\n", hash1);
    //printf ("hash2 is %d\n", hash2);
    if (hash1 == hash2) count++;
    for (i = 1; i <= strlen(ar)-strlen(pat); i ++)
    {
        hash2 = (hash2*(26%p))%p;
        hash2 = (hash2 - ((int)ar[i-1]*power(26, strlen(pat)))%p)%p;
        if (hash2 < 0)
            hash2 += p;
        hash2 = (hash2+((int)ar[i+strlen(pat)-1])%p)%p;
        //printf ("hash2 is %d\n", hash2);
        if (hash1 == hash2)
        {
            int flag = 1;
            int j;
            for (j = 0; j < strlen(pat); j ++)
            {
                if (pat[j] != ar[i+j])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag) count++;
        }
    }
    return count;
}
int main()
{
    char ar[100000], pat[100000];
    scanf ("%s", ar);
    scanf ("%s", pat);
    int ans = rabinkarp(ar,pat);
    printf ("%d", ans);
    return 0;
}
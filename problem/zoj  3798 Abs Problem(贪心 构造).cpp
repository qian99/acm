#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 50000+10;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n%4 == 0)
        {
            printf("0 %d\n",n);
            for(int i = 1;i <= n;++i)
            {
                if(i>1) printf(" ");
                printf("%d %d %d %d",i,i+1,i+3,i+2);
                i += 3;
            }
            printf("\n");
            for(int i = n-1;i > 3;--i)
            {
                if(i < n - 1) printf(" ");
                printf("%d %d %d %d",i,i-1,i-2,i-3);
                i -= 3;
            }
            if(n > 4) printf(" ");
            printf("1 3 2 %d\n",n);
        }
        else if(n % 4 == 1)
        {
            if(n == 1)
            {
                puts("1 1");
                puts("1");
                puts("1");
                continue;
            }
            printf("1 %d\n",n);
            for(int i = n;i > 1;--i)
            {
                if (i < n) printf(" ");
                printf("%d %d %d %d",i,i-1,i-2,i-3);
                i -= 3;
            }
            printf(" 1\n");
            for(int i = n-1;i >= 1;--i)
            {
                if (i < n-1) printf(" ");
                printf("%d %d %d %d",i,i-1,i-2,i-3);
                i -= 3;
            }
            printf(" %d\n",n);
        }
        else if(n%4 == 2)
        {
            printf("1 %d\n",n-1);
            for(int i = n ;i >= 3;--i)
            {
                if(i < n) printf(" ");
                printf("%d %d %d %d",i,i-1,i-2,i-3);
                i -= 3;
            }
            if(n > 2) printf(" ");
            printf("1 2\n");
            for(int i = n-1;i >= 2;--i)
            {
                if(i < n-1) printf(" ");
                printf("%d %d %d %d",i,i-1,i-2,i-3);
                i -= 3;
            }
            if(n > 2) printf(" ");
            printf("1 %d\n",n);
        }
        else
        {
            printf("0 %d\n",n-1);
            for(int i = n;i >= 4;--i)
            {
                if(i < n) printf(" ");
                printf("%d %d %d %d",i,i-1,i-2,i-3);
                i -= 3;
            }
            if(n > 3) printf(" ");
            printf("3 2 1\n");
            for(int i = n-1;i >= 3;--i)
            {
                if(i < n-1) printf(" ");
                printf("%d %d %d %d",i,i-1,i-2,i-3);
                i -= 3;
            }
            if(n > 3) printf(" ");
            printf("1 2 %d\n",n);
        }
    }
    return 0;
}
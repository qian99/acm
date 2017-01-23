#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int main()
{
    //freopen("a.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        int k=(n&1)?n+2:n+1;
        int x,y;
        if(n>2) printf("%d",n);
        for(int i=n;i>2;i--)
        {
            x=i;y=n;
            while(x<=n&&y>=1)
            {
                printf(" %d",(x-1)*n+y);
                x++;y--;
            }
        }
        if(n>2) printf("\n");
        if(n>=2)
        {
            printf("%d",k);
            k+=2;
            x=2;y=n;
            while(x<=n&&y>=1)
            {
                printf(" %d",(x-1)*n+y);
                x++;y--;
            }
            printf("\n");
        }
        for(int i=n;i>=2;i--)
        {
            printf("%d",k);
            k+=2;
            x=1,y=i;
            printf(" %d",(x-1)*n+y);
            x++;y--;
            while(x<=n&&y>=1)
            {
                printf(" %d",(x-1)*n+y);
                x++;y--;
            }
            printf("\n");
        }
    }
    return 0;
}

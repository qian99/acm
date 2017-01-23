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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100 + 10;
char str[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&tcase);
        getchar();
        gets(str);
        int n = strlen(str);
        int m,x,pos = 0;
        scanf("%d",&m);
        printf("%d ",tcase);
        for(int i = 0;i < m;++i)
        {
            scanf("%d",&x);
            pos += x;
            pos = (pos%n + n)%n;
            putchar(str[pos]);
        }
        puts("");
    }
    return 0;
}


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
const int maxn = 100000 + 10;
int ans[maxn];
int f(int x)
{
    if(x == 1) return 1;
    if(x < maxn && ans[x] != -1) return ans[x];
    int res = x;
    if(x & 1)
        res = max(res,f(x*3 + 1));
    else
        res = max(res,f(x/2));
    if(x < maxn)
    {
        ans[x] = res;
    }
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    memset(ans,0xff,sizeof(ans));
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,tcase;
        scanf("%d%d",&tcase,&n);
        printf("%d %d\n",tcase,f(n));
    }
    return 0;
}

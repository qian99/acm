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
const int maxn = 30000000 + 1;
int gcd(int a,int b) {return b == 0?a:gcd(b,a%b);}
ll ans[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    memset(ans,0,sizeof(ans));
    for(int i = 1;i < maxn;++i)
    {
        for(int j = i + i;j < maxn;j += i)
        {
            if((j - (i^j)) == i)
            {
                ans[j]++;
            }
        }
    }
    for(int i = 1;i < maxn;++i)
        ans[i] += ans[i-1];
    int t,tcase = 0,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        printf("Case %d: %lld\n",++tcase,ans[n]);
    }
    return 0;
}


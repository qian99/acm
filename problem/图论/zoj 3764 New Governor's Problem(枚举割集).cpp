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
const int maxn=1000+10;
struct Edge
{
    int u,v,cap;
}edges[maxn];
int n,m,k;
int num[maxn];
inline bool check(int st,int u,int v)
{
    return ((st&(1<<u))&&!(st&(1<<v)))||((st&(1<<v))&&!(st&(1<<u)));
}
ll solve()
{
    ll ans=Inf,sum;
    int u,v,cnt;
    for(int i=0;i<(1<<n);++i)
    {
        if(!(i&1)) continue;
        if(i&(1<<(n-1))) continue;
        cnt=0;
        for(int j=0;j<m;++j)
        {
            u=edges[j].u;
            v=edges[j].v;
            if(check(i,u,v))
                num[cnt++]=edges[j].cap;
        }
        sort(num,num+cnt);
        sum=0;
        for(int j=0;j<cnt-k;++j)
            sum+=num[j];
        ans=min(ans,sum);
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&edges[i].u,&edges[i].v,&edges[i].cap);
            edges[i].u--;edges[i].v--;
        }
        printf("%lld\n",solve());
    }
    return 0;
}

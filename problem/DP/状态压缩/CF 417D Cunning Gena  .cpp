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
const int maxn=100+10;
struct Node
{
    int x,k,msk;
    bool operator <(const Node &a) const
    {
        return k<a.k;
    }
}node[maxn];
ll dp[1<<20];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,b;
    scanf("%d%d%d",&n,&m,&b);
    int N=1<<m,tot,v;
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&node[i].x,&node[i].k,&tot);
        node[i].msk=0;
        while(tot--)
        {
            scanf("%d",&v);v--;
            node[i].msk|=(1<<v);
        }
    }
    sort(node+1,node+n+1);
    ll ans=Inf,tmp;
    for(int i=0;i<N;++i) dp[i]=Inf;
    dp[0]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<N;++j)
        {
            dp[j|node[i].msk]=min(dp[j|node[i].msk],dp[j]+node[i].x);
        }
        if(dp[N-1]==Inf) continue;
        tmp=dp[N-1]+(ll)b*node[i].k;
        if(tmp<ans) ans=tmp;
    }
    if(ans==Inf) printf("-1\n");
    else printf("%I64d\n",ans);
    return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
const int maxm=100000+10;
struct Edge
{
    int u,v,w;
    bool operator < (const Edge & a) const
    {
        return w>a.w;
    }
};
int parents[maxn],flag[maxn],sum[maxn];
Edge edges[maxm];
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
void Uion(int x,int y,int w)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        if(flag[a]+flag[b]>=2) return ;
        parents[b]=a;
        sum[a]+=sum[b]+w;
        flag[a]|=flag[b];
        return ;
    }
    if(!flag[a])
    {
        sum[a]+=w;
        flag[a]=1;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        for(int i=0;i<=n;++i) parents[i]=i;
        for(int i=0;i<m;++i)
          scanf("%d%d%d",&edges[i].u,&edges[i].v,&edges[i].w);
        sort(edges,edges+m);
        memset(sum,0,sizeof(sum));
        memset(flag,0,sizeof(flag));
        for(int i=0;i<m;++i)
          Uion(edges[i].u,edges[i].v,edges[i].w);
        int ans=0;
        for(int i=0;i<n;++i)
          if(parents[i]==i)
            ans+=sum[i];
        printf("%d\n",ans);
    }
    return 0;
}

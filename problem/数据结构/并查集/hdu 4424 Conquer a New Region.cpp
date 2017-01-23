#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int maxn=200000+10;
struct Edge
{
    int u,v;
    ll w;
    bool operator < (const Edge &e )const
    {
        return w>e.w;
    }
};
Edge edges[maxn];
int cnt[maxn],parents[maxn];
ll sum[maxn];
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
void Uion(int x,int y,ll v)
{
    int a=Find(x);
    int b=Find(y);
    ll ta=sum[a]+cnt[b]*v;
    ll tb=sum[b]+cnt[a]*v;
    if(ta>tb)
    {
        sum[a]=ta;
        cnt[a]+=cnt[b];
        parents[b]=a;
    }
    else
    {
        sum[b]=tb;
        cnt[b]+=cnt[a];
        parents[a]=b;
    }
}
void Init(int n)
{
    for(int i=1;i<=n;++i)
    {
        parents[i]=i;
        sum[i]=0;
        cnt[i]=1;
    }
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        int i;
        Init(n);
        for(i=0;i<n-1;++i)
          scanf("%d%d%I64d",&edges[i].u,&edges[i].v,&edges[i].w);
        sort(edges,edges+n-1);
        for(i=0;i<n-1;++i)
        {
            Uion(edges[i].u,edges[i].v,edges[i].w);
        }
        printf("%I64d\n",sum[Find(1)]);
    }
    return 0;
}

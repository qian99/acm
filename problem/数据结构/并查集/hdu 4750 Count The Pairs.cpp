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
const int maxn=10000+10;
const int maxm=500000+10;
struct Edge
{
    int u,v,w;
    bool operator <(const Edge &a) const
    {
        return w<a.w;
    }
};
Edge edges[maxm],e[maxm];
int parents[maxn],num[maxn],len[maxn],zz;
ll sum[maxn],ans;
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
bool Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(b!=a)
    {
        parents[b]=a;
        return true;
    }
    return false;
}
void Uion2(int x,int y,int w)
{
    int a=Find(x);
    int b=Find(y);
    if(b!=a)
    {
        ans+=num[a]*num[b]*2;
        num[a]+=num[b];
        zz++;
        sum[zz]=ans;
        len[zz]=w;
        parents[b]=a;
    }
}
void Init(int n)
{
    for(int i=0;i<n;++i)
      parents[i]=i;
    zz=ans=0;
    sum[0]=0;
}
int f(int l,int r,int v)
{
    int m;
    if(len[l]>=v) return 0;
    if(len[r]<v) return r;
    int pos=-1;
    while(l<r)
    {
        m=(l+r)>>1;
        if(len[m]>=v)
          r=m-1;
        else {l=m+1;pos=m;}
    }
    if(len[l]<v) pos=max(pos,l);
    return pos;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        Init(n);
        for(int i=0;i<m;++i)
          scanf("%d%d%d",&edges[i].u,&edges[i].v,&edges[i].w);
        sort(edges,edges+m);
        int cnt=0;
        for(int i=0;i<m;++i)
        {
            if(Uion(edges[i].u,edges[i].v))
                e[++cnt]=edges[i];
        }
        sort(e+1,e+cnt+1);
        for(int i=0;i<n;++i)
        {
            parents[i]=i;
            num[i]=1;
        }
        for(int i=1;i<=cnt;++i)
          Uion2(e[i].u,e[i].v,e[i].w);
        int q,t;
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d",&t);
            int pos=f(1,cnt,t);
            ll res=ans-sum[pos];
            printf("%I64d\n",res);
        }
    }
    return 0;
}

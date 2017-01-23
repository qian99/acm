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
const int maxn=20000+10;
const int maxm=50000+10;
struct Edge
{
    int u,v,w;
    bool operator < (const Edge &a) const
    {
        return w<a.w;
    }
};
Edge edges[maxm];
int parents[maxn];
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
bool Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        parents[b]=a;
        return true;
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m,r;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&r);
        int N=n+m;
        int ans=N*10000;
        for(int i=0;i<=N;++i)
          parents[i]=i;
        int u,v,w;
        for(int i=0;i<r;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            edges[i].u=u;edges[i].v=v+n;
            edges[i].w=-w;
        }
        sort(edges,edges+r);
        for(int i=0;i<r;++i)
        {
            u=edges[i].u;v=edges[i].v;
            if(Uion(u,v))
              ans+=edges[i].w;
        }
        printf("%d\n",ans);
    }
    return 0;
}

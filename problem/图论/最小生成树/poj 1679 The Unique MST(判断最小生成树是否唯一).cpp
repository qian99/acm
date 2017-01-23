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
const int maxn=100+10;
const int maxm=maxn*maxn;
struct Edge
{
    int u,v,w;
    Edge(){};
    Edge(int uu,int vv,int ww){u=uu;v=vv;w=ww;}
    bool operator <(const Edge & a) const
    {
        return w<a.w;
    }
}edges[maxm];
int parents[maxn],flag[maxm];
int n,m;
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
int kruskal()
{
    for(int i=0;i<=n;++i) parents[i]=i;
    int cnt=0,res=0;
    int a,b;
    for(int i=0;i<m;++i)
    {
        a=Find(edges[i].u);
        b=Find(edges[i].v);
        if(a!=b&&flag[i]!=3)
        {
            parents[b]=a;
            res+=edges[i].w;
            cnt++;
        }
    }
    if(cnt!=n-1) return -inf;
    return res;
}
int solve()
{
    memset(flag,0,sizeof(flag));
    sort(edges,edges+m);
    for(int i=0;i<m-1;++i)
        if(edges[i].w==edges[i+1].w)
            flag[i]=flag[i+1]=1;
    int res=0,res2=0,a,b;
    bool used=false;
    for(int i=0;i<=n;++i) parents[i]=i;
    for(int i=0;i<m;++i)
    {
        a=Find(edges[i].u);
        b=Find(edges[i].v);
        if(a!=b)
        {
            parents[b]=a;
            res+=edges[i].w;
            if(flag[i]) {flag[i]=2;used=true;}
        }
    }
    if(!used) return res;
    for(int i=0;i<m;++i)
    {
        if(flag[i]==2)
        {
            flag[i]=3;
            res2=kruskal();
            if(res2==res) return -inf;
            flag[i]=2;
        }
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            edges[i]=Edge(u,v,w);
        }
        int ans=solve();
        if(ans==-inf)
            printf("Not Unique!\n");
        else
            printf("%d\n",ans);
    }
    return 0;
}


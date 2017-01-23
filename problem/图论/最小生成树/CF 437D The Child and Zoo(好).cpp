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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
struct Edge
{
    int u,v,w;
    Edge(){}
    Edge(int u,int v,int w):u(u),v(v),w(w){}
    bool operator <(const Edge &a) const
    {
        return w>a.w;
    }
}edges[maxn];
int parents[maxn],size[maxn],a[maxn];
double ans,n;
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
        ans+=(double)size[a]*size[b]*w;
        size[a]+=size[b];
        parents[b]=a;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;++i) parents[i]=i,size[i]=1;
    int u,v;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&u,&v);
        edges[i]=Edge(u,v,min(a[u],a[v]));
    }
    sort(edges,edges+m);
    ans=0;
    for(int i=0;i<m;++i)
        Uion(edges[i].u,edges[i].v,edges[i].w);
    ans=ans/n/(n-1);
    printf("%.10lf\n",ans*2);
    return 0;
}
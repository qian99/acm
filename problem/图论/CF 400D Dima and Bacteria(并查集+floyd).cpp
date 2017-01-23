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
const int maxn=100000+10;
struct Edge
{
    int v,w,next;
    Edge(){}
    Edge(int v,int w,int next):v(v),w(w),next(next){}
}edges[maxn<<1];
int head[maxn],nEdge;
int type[maxn],c[maxn];
int pa[maxn];
int d[550][550];
void AddEdges(int u,int v,int w)
{
    edges[++nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,w,head[v]);
    head[v]=nEdge;
}
int Find(int x)
{
    return x==pa[x]?x:pa[x]=Find(pa[x]);
}
void Uion(int x,int y)
{
    int a=Find(x),b=Find(y);
    if(a!=b) pa[b]=a;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    int cnt=0,u,v,w;
    memset(head,0xff,sizeof(head));
    memset(d,0x3f,sizeof(d));
    nEdge=-1;
    for(int i=1;i<=n;++i) pa[i]=i;
    for(int i=1;i<=k;++i)
    {
        scanf("%d",&c[i]);
        for(int j=0;j<c[i];++j)
            type[++cnt]=i;
    }
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        AddEdges(u,v,w);
        if(w==0)
            Uion(u,v);
        if(type[u]!=type[v])
            d[type[u]][type[v]]=d[type[v]][type[u]]=min(d[type[u]][type[v]],w);
    }
    cnt=1;
    bool flag=true;
    for(int i=1;i<=k&&flag;++i)
    {
        int fa=Find(cnt);
        for(int j=0;j<c[i];++j)
            if(Find(cnt+j)!=fa) {flag=false;break;}
        cnt+=c[i];
    }
    if(!flag)
        printf("No\n");
    else
    {
        for(int i=1;i<=k;++i) d[i][i]=0;
        for(int v=1;v<=k;++v)
            for(int i=1;i<=k;++i)
                for(int j=1;j<=k;++j)
                    d[i][j]=min(d[i][j],d[i][v]+d[v][j]);
        printf("Yes\n");
        for(int i=1;i<=k;++i)
        {
            for(int j=1;j<=k;++j)
            {
                if(j!=1) printf(" ");
                if(d[i][j]==inf) d[i][j]=-1;
                printf("%d",d[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}

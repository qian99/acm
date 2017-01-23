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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
struct Edge
{
    int v,next;
    Edge(){};
    Edge(int v,int next):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],d[maxn],nEdge;
double A[maxn],B[maxn],C[maxn];
double K[maxn],E[maxn],P[maxn];
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
bool dfs(int u,int fa)
{
    A[u]=B[u]=C[u]=0;
    double tmp=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        if(!dfs(v,u)) return false;
        tmp+=P[u]/d[u]*B[v];
        A[u]+=P[u]/d[u]*A[v];
        C[u]+=P[u]/d[u]*C[v];
    }
    if(fabs(1-tmp)<eps) return false;
    if(d[u]==1&&fa!=-1)
    {
        A[u]=K[u];
        C[u]=B[u]=P[u];
    }
    else
    {
        tmp=1-tmp;
        A[u]=(A[u]+K[u])/tmp;
        B[u]=P[u]/d[u]/tmp;
        C[u]=(P[u]+C[u])/tmp;
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        memset(head,0xff,sizeof(head));
        memset(d,0,sizeof(d));
        nEdge=-1;
        scanf("%d",&n);
        int u,v;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
            d[u]++;d[v]++;
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&u,&v);
            K[i]=u/100.0;
            E[i]=v/100.0;
            P[i]=(100-u-v)/100.0;
        }
        printf("Case %d: ",tcase);
        if(dfs(1,-1)&&fabs(A[1]-1)<eps)
            printf("impossible\n");
        else printf("%.6lf\n",C[1]/(1-A[1]));
    }
    return 0;
}

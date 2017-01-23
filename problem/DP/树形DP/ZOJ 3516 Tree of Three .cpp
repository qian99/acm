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
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],val[maxn],nEdge,dfs_clock;
int ans[maxn][3];
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(ans,0xff,sizeof(ans));
    nEdge=-1;dfs_clock=0;
}
void cal(int a[3],int b[3])
{
    for(int i=0;i<3;++i)
    {
        if(a[0]<b[i])
        {
            a[2]=a[1];
            a[1]=a[0];
            a[0]=b[i];
        }
        else if(a[1]<b[i])
        {
            a[2]=a[1];
            a[1]=b[i];
        }
        else if(a[2]<b[i])
            a[2]=b[i];
    }
}
void dfs(int u)
{
    ans[u][0]=val[u];
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        dfs(v);
        cal(ans[u],ans[v]);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        Init();
        scanf("%d",&val[0]);
        int u;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&val[i]);
            AddEdges(u,i);
        }
        dfs(0);
        int q;
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d",&u);
            if(ans[u][2]==-1) printf("-1\n");
            else printf("%d %d %d\n",ans[u][0],ans[u][1],ans[u][2]);
        }
    }
    return 0;
}

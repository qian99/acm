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
const int maxn=100000+10;
const int maxm=1000000+10;
int ch[maxm][26],val[maxm],size;
char str[20];
int Insert(const char *s,int v)
{
    int u=0,n=strlen(s);
    int fa=-1;
    for(int i=0;i<n;++i)
    {
        int c=s[i]-'a';
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            memset(ch[size],0,sizeof(ch[size]));
            val[size]=0;
        }
        u=ch[u][c];
        if(val[u]) fa=val[u];
    }
    val[u]=v;
    return fa;
}
int pa[maxn];
struct Edge
{
    int v,next;
    Edge (){};
    Edge(int vv,int nx) {v=vv;next=nx;}
}edges[maxn<<1];
int head[maxn<<1],nEdge,w[maxn],res[maxn];
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    val[0]=size=0;
    memset(head,0xff,sizeof(head));
    nEdge=-1;
}
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void dfs(int u,int fa)
{
    res[u]=w[u];
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        dfs(v,u);
        res[u]+=res[v];
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        Init();
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%s",str);
            pa[i]=Insert(str,i);
            if(pa[i]!=-1) AddEdges(i,pa[i]);
        }
        for(int i=1;i<=n;++i)
            scanf("%d",&w[i]);
        for(int i=1;i<=n;++i)
            if(pa[i]==-1) dfs(i,-1);
        for(int i=1;i<=n;++i)
        {
            if(i!=1) printf(" ");
            printf("%d",res[i]);
        }
        printf("\n");
    }
    return 0;
}

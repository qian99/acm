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
const int maxn=55;
const int maxm=1000+10;
struct Edge
{
    int v,w,next;
    Edge(){}
    Edge(int v,int w,int next):v(v),w(w),next(next){}
}edges[maxm<<1];
struct Node
{
    int u,st;
    Node(){}
    Node(int u,int st):u(u),st(st){}
};
int head[maxn],nEdge;
void AddEdges(int u,int v,int w)
{
    edges[++nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,w,head[v]);
    head[v]=nEdge;
}
int d[maxn][1<<11],dp[1<<11],msk[maxn],n,m,k;
bool inq[maxn][1<<11];
queue<Node>q;
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(dp,0x3f,sizeof(dp));
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(q));
    nEdge=-1;
    memset(msk,0,sizeof(msk));
    for(int i=1;i<=k;++i)
    {
        msk[i]=1<<(i-1);
        msk[n-k+i]=1<<(k+i-1);
        d[i][msk[i]]=0;d[n-k+i][msk[n-k+i]]=0;
    }
}
void spfa()
{
    Node node;
    while(!q.empty())
    {
        node=q.front();q.pop();
        int u=node.u,state=node.st,v;
        inq[u][state]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            v=edges[k].v;
            if(d[v][state|msk[v]]>d[u][state]+edges[k].w)
            {
                d[v][state|msk[v]]=d[u][state]+edges[k].w;
                if(!inq[v][state]) {inq[v][state]=true;q.push(Node(v,state));}
            }
        }
    }
}
void Steiner_Tree()
{
    int tot=1<<(2*k);
    for(int i=0;i<tot;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=i&(i-1);k;k=(k-1)&i)
                d[j][i]=min(d[j][i],d[j][k|msk[j]]+d[j][(i-k)|msk[j]]);
            if(d[j][i]<inf) {inq[j][i]=true;q.push(Node(j,i));}
        }
        spfa();
    }
}
bool check(int state)
{
    int ret=0;
    for(int i=1;i<=k;++i)
    {
        if(state&msk[i]) ret++;
        if(state&msk[n-k+i]) ret--;
    }
    return ret==0;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&k);
        Init();
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v,w);
        }
        Steiner_Tree();
        int tot=1<<(2*k);
        for(int i=0;i<tot;++i)
            for(int j=1;j<=n;++j)
                dp[i]=min(dp[i],d[j][i]);
        for(int i=1;i<tot;++i)
        {
            if(!check(i)) continue;
            for(int j=i&(i-1);j;j=(j-1)&i)
            {
                if(check(j))
                    dp[i]=min(dp[i],dp[j]+dp[i-j]);
            }
        }
        if(dp[tot-1]==inf) printf("No solution\n");
        else printf("%d\n",dp[tot-1]);
    }
    return 0;
}

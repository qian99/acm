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
const int maxn=200+10;
const int maxm=5000+10;
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
int d[maxn][1<<11],dp[1<<11],msk[maxn],type[15],n,m,K;
bool inq[maxn][1<<11];
queue<Node>q;
void AddEdges(int u,int v,int w)
{
    edges[++nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,w,head[v]);
    head[v]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    memset(d,0x3f,sizeof(d));
    memset(dp,0x3f,sizeof(dp));
    memset(inq,0,sizeof(inq));
    memset(msk,0,sizeof(msk));
    memset(type,0,sizeof(type));
    int u,v,w;
    K=0;
    bool flag;
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&u,&v);
        if(u||v) flag=true;
        else flag=false;
        while(u--)
        {
            msk[i]|=(1<<K);
            type[K]=1;
            K++;
        }
        if(v)
        {
            msk[i]|=(1<<K);
            type[K]=-1;
            K++;
        }
        if(flag) d[i][msk[i]]=0;
    }
    scanf("%d",&m);
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        AddEdges(u,v,w);
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
                if((state|msk[v])==state&&!inq[v][state]) {inq[v][state]=true;q.push(Node(v,state));}
            }
        }
    }
}
void Steiner_Tree()
{
    for(int i=1;i<(1<<K);++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(msk[j]&&((msk[j]&i)!=msk[j])) continue;
            for(int k=i&(i-1);k;k=(k-1)&i)
                d[j][i]=min(d[j][i],d[j][k|msk[j]]+d[j][(i-k)|msk[j]]);
            if(d[j][i]<inf) {inq[j][i]=true;q.push(Node(j,i));}
        }
        spfa();
    }
}
bool check(int x)
{
    int ret=0;
    for(int i=0;i<K;++i)
        if(x&(1<<i)) ret+=type[i];
    return ret>=0;
}
int cal(int x)
{
    int ret=0;
    for(int i=0;i<K;++i)
        if(x&(1<<i)) ret+=(type[i]<0)?1:0;
    return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        Init();
        Steiner_Tree();
        for(int i=0;i<(1<<K);++i)
            for(int j=1;j<=n;++j)
                dp[i]=min(dp[i],d[j][i]);
        int maxf=0,minv=0;
        for(int i=1;i<(1<<K);++i)
            if(check(i))
            {
                for(int j=(i-1)&i;j;j=(j-1)&i)
                {
                    if(check(j)&&check(i-j))
                        dp[i]=min(dp[i],dp[j]+dp[i-j]);
                }
                int tmp=cal(i);
                if(dp[i]<inf&&(tmp>maxf||(tmp==maxf&&dp[i]<minv)))
                {
                    maxf=tmp;
                    minv=dp[i];
                }
            }
        if(maxf<=0) maxf=minv=0;
        printf("%d %d\n",maxf,minv);
    }
    return 0;
}

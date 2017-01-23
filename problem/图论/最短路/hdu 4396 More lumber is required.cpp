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
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=5000+10;
const int maxm=100000+10;
struct Edge
{
    int v,w,next;
    Edge(){}
    Edge(int v,int w,int next):v(v),w(w),next(next){}
}edges[maxm<<1];
int head[maxn],nEdge;
void AddEdges(int u,int v,int w)
{
    edges[++nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,w,head[v]);
    head[v]=nEdge;
}
int d[maxn][555];
bool inq[maxn][555];
int spfa(int s,int t,int K)
{
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    queue<pair<int,int> >q;
    q.push(make_pair(s,0));
    d[s][0]=0;
    int u,x;
    while(!q.empty())
    {
        u=q.front().first;
        x=q.front().second;
        q.pop();
        inq[u][x]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            int y=min(K,x+10);
            if(d[v][y]>d[u][x]+edges[k].w)
            {
                d[v][y]=d[u][x]+edges[k].w;
                if(!inq[v][y]) {inq[v][y]=true;q.push(make_pair(v,y));}
            }
        }
    }
    if(d[t][K]==inf) return -1;
    return d[t][K];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    int u,v,w,s,t,K;
    while(~scanf("%d%d",&n,&m))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v,w);
        }
        scanf("%d%d%d",&s,&t,&K);
        int ans=spfa(s,t,K);
        printf("%d\n",ans);
    }
    return 0;
}

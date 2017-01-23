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
const int maxm=100000+10;
const int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
struct Edge
{
    int from,to,cap,flow,cost,next;
    Edge(){};
    Edge(int ff,int tt,int cc,int fl,int co,int nx)
    {from=ff;to=tt;cap=cc;flow=fl;cost=co;next=nx;}
}edges[maxm<<1];
int head[maxn],nEdge;
int d[maxn],p[maxn],a[maxn];
int A[15][15],val[maxn],indx[15][15],tp[15][15];
bool inq[maxn];
void AddEdges(int from,int to,int cap,int cost)
{
    edges[++nEdge]=Edge(from,to,cap,0,cost,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(to,from,0,0,-cost,head[to]);
    head[to]=nEdge;
}
bool spfa(int s,int t,int &flow,int &cost)
{
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    queue<int>q;
    q.push(s);
    d[s]=0;a[s]=inf;p[s]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(e.cap>e.flow&&d[e.to]>d[u]+e.cost)
            {
                d[e.to]=d[u]+e.cost;
                p[e.to]=k;
                a[e.to]=min(a[u],e.cap-e.flow);
                if(!inq[e.to]){inq[e.to]=true;q.push(e.to);}
            }
        }
    }
    if(d[t]==inf) return false;
    if(d[t]>=0) return false;
    flow+=a[t];
    cost+=a[t]*d[t];
    int u=t;
    while(u!=s)
    {
        edges[p[u]].flow+=a[t];
        edges[p[u]^1].flow-=a[t];
        u=edges[p[u]].from;
    }
    return true;
}
void mincost(int s,int t,int &flow,int &cost)
{
    flow=0,cost=0;
    while(spfa(s,t,flow,cost));
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        int n,m,k;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        scanf("%d%d%d",&n,&m,&k);
        int S=0,T=2*n*m+1,cnt=0,type=0;
        int tot=0;
        for(int i=0;i<n;++i)
        {
            type=i&1;
            for(int j=0;j<m;++j)
            {
                scanf("%d",&A[i][j]);
                val[++cnt]=A[i][j];
                indx[i][j]=cnt;tp[i][j]=type;
                tot+=val[cnt]*val[cnt];
                for(int kk=1;kk<=17;kk+=2)
                    AddEdges(cnt,cnt+n*m,1,kk-2*A[i][j]);
                if(type==0) AddEdges(S,cnt,k,0);
                else AddEdges(cnt+n*m,T,k,0);
                type^=1;
            }
        }
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
            {
                if(tp[i][j]!=0) continue;
                int x,y;
                for(int kk=0;kk<4;++kk)
                {
                    x=i+dir[kk][0];
                    y=j+dir[kk][1];
                    if(x>=0&&x<n&&y>=0&&y<m)
                        AddEdges(indx[i][j]+n*m,indx[x][y],inf,0);
                }
            }
        int flow,cost;
        mincost(S,T,flow,cost);
        int ans=tot+cost;
        printf("Case %d: %d\n",tcase,ans);
    }
    return 0;
}

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
const int maxn=1000+10;
const int maxm=200000+10;
struct Edge
{
    int to,cap,flow,next;
    Edge(){}
    Edge(int to,int cap,int flow,int next):to(to),cap(cap),flow(flow),next(next){}
}edges[maxm<<1];
int head[maxn],d[maxn],cur[maxn],nEdge;
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(to,cap,0,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,0,head[to]);
    head[to]=nEdge;
}
bool BFS(int s,int t)
{
    memset(d,0xff,sizeof(d));
    d[s]=0;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(d[e.to]==-1&&e.cap>e.flow)
            {
                d[e.to]=d[u]+1;
                q.push(e.to);
            }
        }
    }
    return d[t]!=-1;
}
ll DFS(int u,int a,int t)
{
    if(u==t||a==0) return a;
    ll flow=0;
    int f;
    for(int &k=cur[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow),t))>0)
        {
            edges[k].flow+=f;
            edges[k^1].flow-=f;
            flow+=f;a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
ll MaxFlow(int s,int t)
{
    ll flow=0;
    while(BFS(s,t))
    {
        for(int i=0;i<=t;++i) cur[i]=head[i];
        flow+=DFS(s,inf,t);
    }
    return flow;
}
int val[maxn],xval[maxn];
vector<int>L,R;
ll gcd(ll a,ll b)
{
    ll c;
    while(b)
    {
        c=a%b;
        a=b;
        b=c;
    }
    return a;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,p;
    while(~scanf("%d%d",&n,&p))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        L.clear();R.clear();
        int x,y,S=0,T=n+1;
        ll sum=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&x,&y);
            if((x^y)&1) L.push_back(i);
            else R.push_back(i);
            val[i]=(x&y);
            xval[i]=(x^y);
            sum+=val[i];
        }
        for(int i=0;i<(int)L.size();++i)
            for(int j=0;j<(int)R.size();++j)
            {
                if(gcd(xval[L[i]]^xval[R[j]],p)<=1)
                    AddEdges(L[i],R[j],inf);
            }
        for(int i=0;i<(int)L.size();++i)
            AddEdges(S,L[i],val[L[i]]);
        for(int i=0;i<(int)R.size();++i)
            AddEdges(R[i],T,val[R[i]]);
        ll ans=sum-MaxFlow(S,T);
        printf("%lld\n",ans);
    }
    return 0;
}

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
const int maxn=1000+10;
struct Edge
{
    int from,to,cap,flow,next;
    Edge(){};
    Edge(int ff,int tt,int cc,int fl,int nx){from=ff;to=tt;cap=cc;flow=fl;next=nx;};
}edges[maxn<<2];
int ind[30],outd[30],parents[30];
int head[30],d[maxn],cur[maxn],nEdge;
bool vis[maxn];
void Init()
{
    memset(ind,0,sizeof(ind));
    memset(outd,0,sizeof(outd));
    memset(head,0xff,sizeof(head));
    for(int i=0;i<30;++i) parents[i]=i;
    nEdge=-1;
}
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(from,to,cap,0,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(to,from,0,0,head[to]);
    head[to]=nEdge;
}
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
bool BFS(int S,int T)
{
    memset(vis,0,sizeof(vis));
    memset(d,0,sizeof(d));
    queue<int>q;
    vis[S]=true;
    q.push(S);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(!vis[e.to]&&e.cap>e.flow)
            {
                d[e.to]=d[u]+1;
                vis[e.to]=true;
                q.push(e.to);
            }
        }
    }
    return vis[T];
}
int DFS(int u,int a,int T)
{
    if(u==T||a==0) return a;
    int flow=0,f;
    for(int & k=cur[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow),T))>0)
        {
            edges[k].flow+=f;
            edges[k^1].flow-=f;
            flow+=f;a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
int Maxflow(int S,int T)
{
    int flow=0;
    while(BFS(S,T))
    {
        for(int i=0;i<=T;++i) cur[i]=head[i];
        flow+=DFS(S,inf,T);
    }
    return flow;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0,n,type;
    char str[30];
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        Init();
        scanf("%d",&n);
        int cnt=0,u,v,len;
        bool flag=true;
        for(int i=0;i<n;++i)
        {
            scanf("%s%d",str,&type);
            len=strlen(str);
            u=(str[0]-'a'+1);
            v=(str[len-1]-'a'+1);
            if(type) AddEdges(u,v,1);
            ind[v]++;outd[u]++;
            if(Find(u)!=Find(v))
            {
                parents[Find(v)]=Find(u);
                cnt++;
            }
        }
        int S=0,T=27,odd=0,tmp,sum=0;
        for(int i=1;i<=26;++i)
        {
            if(ind[i]||outd[i])
            {
                cnt--;
                tmp=ind[i]-outd[i];
                if(tmp%2) odd++;
                else
                {
                    if(tmp>0) {AddEdges(i,T,tmp/2);sum+=(tmp/2);}
                    else AddEdges(S,i,(-tmp)/2);
                }
            }
        }
        if(cnt!=-1||(odd!=0&&odd!=2)) flag=false;
        tmp=Maxflow(S,T);
        printf("Case %d: ",tcase);
        if(tmp==sum&&flag)
            printf("Well done!\n");
        else
            printf("Poor boy!\n");
    }
    return 0;
}


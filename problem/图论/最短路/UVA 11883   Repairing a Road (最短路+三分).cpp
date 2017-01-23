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
const int maxn=100+10;
const int maxm=500+10;
struct Edge
{
    int v;
    double vi,ai;
    int next;
    Edge(){}
    Edge(int v,double vi,double ai,int next):v(v),vi(vi),ai(ai),next(next){}
}edges[maxm<<1];
int head[maxn],nEdge;
bool inq[maxn][2];
double d[maxn][2];
void AddEdges(int u,int v,double w1,double w2)
{
    edges[++nEdge]=Edge(v,w1,w2,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,w1,w2,head[v]);
    head[v]=nEdge;
}
inline double F(double x,double t,double vi,double ai)
{
    return x+t+vi*pow(ai,-t-x);
}
double cal(double x,double vi,double ai)
{
    double L=0,R=vi;
    for(int i=0;i<50;++i)
    {
        double m1=L+(R-L)/3;
        double m2=R-(R-L)/3;
        if(F(m1,x,vi,ai)>F(m2,x,vi,ai)) L=m1;
        else R=m2;
    }
    return F(L,x,vi,ai);
}
double spfa(int n)
{
    queue<pair<int,int> >q;
    memset(inq,0,sizeof(inq));
    for(int i=0;i<=n;++i) d[i][0]=d[i][1]=1e10;
    pair<int,int >pii;
    q.push(make_pair(1,0));
    d[1][0]=0;
    int u,st;
    while(!q.empty())
    {
        pii=q.front();q.pop();
        u=pii.first;st=pii.second;
        inq[u][st]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(d[v][st]>d[u][st]+edges[k].vi)
            {
                d[v][st]=d[u][st]+edges[k].vi;
                if(!inq[v][st]) {inq[v][st]=true;q.push(make_pair(v,st));}
            }
            if(st==0)
            {
                double cost=cal(d[u][0],edges[k].vi,edges[k].ai);
                if(d[v][1]>cost)
                {
                    d[v][1]=cost;
                    if(!inq[v][1]) {inq[v][1]=true;q.push(make_pair(v,1));}
                }
            }
        }
    }
    return min(d[n][0],d[n][1]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v;
        double vi,ai;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%lf%lf",&u,&v,&vi,&ai);
            AddEdges(u,v,vi,ai);
        }
        double ans=spfa(n);
        printf("%.3lf\n",ans);
    }
    return 0;
}

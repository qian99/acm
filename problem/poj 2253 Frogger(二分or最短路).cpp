//二分答案，bfs验证
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
const int maxn=200+10;
const int maxm=maxn*maxn;
struct Point
{
    int x,y;
};
struct Edge
{
    int v,next;
    double w;
};
Edge edges[maxm<<1];
int head[maxn],nEdge,n;
bool vis[maxn];
void AddEdge(int u,int v,double w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
double Len(Point a,Point b)
{
    return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}
Point pt[maxn];
bool test(double maxl)
{
    memset(vis,0,sizeof(vis));
    vis[1]=true;
    queue<int>q;
    q.push(1);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(vis[v]) continue;
            if(edges[k].w<=maxl)
            {
                vis[v]=true;
                q.push(v);
            }
        }
    }
    return vis[2];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        tcase++;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<=n;++i)
          scanf("%d%d",&pt[i].x,&pt[i].y);
        for(int i=1;i<=n;++i)
          for(int j=i+1;j<=n;++j)
          {
              double w=Len(pt[i],pt[j]);
              AddEdge(i,j,w);
              AddEdge(j,i,w);
          }
        double L=0,R=2000;
        while(R-L>eps)
        {
            double m=(L+R)/2;
            if(test(m))
              R=m;
            else
              L=m;
        }
        printf("Scenario #%d\n",tcase);
        printf("Frog Distance = %.3lf\n\n",L);
    }
    return 0;
}




//spfa,d[u]为到u点至少需要的弹跳距离
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
const int maxn=200+10;
const int maxm=maxn*maxn;
struct Point
{
    int x,y;
};
struct Edge
{
    int v,next;
    double w;
};
Edge edges[maxm<<1];
int head[maxn],nEdge,n;
bool inq[maxn];
double d[maxn];
void AddEdge(int u,int v,double w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
double Len(Point a,Point b)
{
    return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}
Point pt[maxn];
double spfa()
{
    memset(inq,0,sizeof(inq));
    for(int i=1;i<=n;++i) d[i]=inf;
    d[1]=0;
    queue<int>q;
    q.push(1);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            double tmp=max(d[u],edges[k].w);
            if(d[v]>tmp)
            {
                d[v]=tmp;
                if(!inq[v]){inq[v]=true;q.push(v);}
            }
        }
    }
    return d[2];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        tcase++;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<=n;++i)
          scanf("%d%d",&pt[i].x,&pt[i].y);
        for(int i=1;i<=n;++i)
          for(int j=i+1;j<=n;++j)
          {
              double w=Len(pt[i],pt[j]);
              AddEdge(i,j,w);
              AddEdge(j,i,w);
          }
        printf("Scenario #%d\n",tcase);
        printf("Frog Distance = %.3lf\n\n",spfa());
    }
    return 0;
}

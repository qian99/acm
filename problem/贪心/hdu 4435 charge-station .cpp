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
const int maxm=40000+10;
struct Point
{
    int x,y;
};
struct Edge
{
    int v,next;
    int w;
};
double Len(Point a,Point b)
{
    return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}
Point pt[maxn];
Edge edges[maxm<<1];
int head[maxn],nEdge,n;
bool flag[maxn],vis[maxn],inq[maxn];
int D;
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void Init()
{
    memset(flag,0,sizeof(flag));
    memset(head,0xff,sizeof(head));
    nEdge=-1;
}
bool bfs()
{
    int cnt=1;
    memset(vis,0,sizeof(vis));
    memset(inq,0,sizeof(inq));
    vis[1]=true;
    queue<int>q;
    q.push(1);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(!vis[v]&&flag[v]&&edges[k].w<=D)
            {
                vis[v]=true;
                cnt++;
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
            if(!vis[v]&&!flag[v]&&edges[k].w<=D/2)
            {
                vis[v]=true;
                cnt++;
            }
        }
    }
    return cnt==n;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&D))
    {
        Init();
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&pt[i].x,&pt[i].y);
            flag[i]=true;
        }
        double tmp;
        int tp;
        for(int i=1;i<=n;++i)
         for(int j=i+1;j<=n;++j)
         {
             tmp=Len(pt[i],pt[j]);
             tp=tmp;
             if(tmp-tp>0) tp++;
//             if(tmp<=D)
//             {
                 AddEdge(i,j,tp);
                 AddEdge(j,i,tp);
//             }
         }
        if(!bfs())
        {
            printf("-1\n");
            continue;
        }
        for(int i=n;i>=2;--i)
        {
            flag[i]=false;
            if(!bfs()) flag[i]=true;
        }
        while(!flag[n]) n--;
        for(int i=n;i>=1;--i)
          if(flag[i]) printf("1");
          else printf("0");
        printf("\n");
    }
    return 0;
}

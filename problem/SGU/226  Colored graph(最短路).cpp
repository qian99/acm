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
const int maxm=100000+10;
struct Edge
{
    int v,color,next;
    Edge(){}
    Edge(int v,int color,int next):v(v),color(color),next(next){}
}edges[maxm];
int head[maxn],nEdge;
int d[maxn][4];
bool inq[maxn][4];
void AddEdge(int u,int v,int c)
{
    edges[++nEdge]=Edge(v,c,head[u]);
    head[u]=nEdge;
}
void spfa()
{
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    queue<pair<int,int> >q;
    pair<int,int>pii;
    for(int i=0;i<3;++i)
    {
        d[1][i]=0;inq[1][i]=true;
        q.push(make_pair(1,i));
    }
    int u,c;
    while(!q.empty())
    {
        pii=q.front();q.pop();
        u=pii.first;c=pii.second;
        inq[u][c]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge &e=edges[k];
            if(e.color==c) continue;
            if(d[e.v][e.color]>d[u][c]+1)
            {
                d[e.v][e.color]=d[u][c]+1;
                if(!inq[e.v][e.color]) {inq[e.v][e.color]=true;q.push(make_pair(e.v,e.color));}
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    scanf("%d%d",&n,&m);
    int u,v,c;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&u,&v,&c);
        AddEdge(u,v,c-1);
    }
    spfa();
    int ans=min(min(d[n][0],d[n][1]),d[n][2]);
    if(ans==inf) ans=-1;
    printf("%d\n",ans);
    return 0;
}

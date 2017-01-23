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
const int maxn=100+10;
const int maxm=1000+10;
struct Edge
{
    int v,w,next;
    Edge(){};
    Edge(int vv,int ww,int nx) {v=vv;w=ww;next=nx;}
}edges[maxm];
int head[maxn],d[maxn][15],nEdge;
bool inq[maxn][15];
void AddEdge(int u,int v,int w)
{
    edges[++nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
}
int spfa(int s,int t)
{
    memset(inq,0,sizeof(inq));
    memset(d,0x3f,sizeof(d));
    d[s][0]=0;
    queue<pair<int,int> >q;
    pair<int,int>tp;
    q.push(make_pair(s,0));
    while(!q.empty())
    {
        tp=q.front();q.pop();
        int u=tp.first,m=tp.second;
        inq[u][m]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            int len=d[u][m]+edges[k].w;
            if(len<d[v][len%10])
            {
                d[v][len%10]=len;
                if(!inq[v][len%10])
                    {inq[v][len%10]=true;q.push(make_pair(v,len%10));}
            }
        }
    }
    for(int i=0;i<10;++i)
    {
        if(d[t][i]<inf) return d[t][i];
    }
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        int s,t;
        scanf("%d%d",&s,&t);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
        }
        int ans=spfa(s,t);
        if(ans<0) printf("Sorry\n");
        else printf("%d\n",ans);
    }
    return 0;
}


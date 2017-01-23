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
const int maxn=3000+10;
map<string,int>mp;
struct Edge
{
    int v,w,next;
    Edge(){}
    Edge(int v,int w,int next):v(v),w(w),next(next){}
}edges[maxn<<2];
int head[maxn],d[maxn][2010],nEdge;
bool flag[maxn],inq[maxn][2010];
void AddEdges(int u,int v,int w)
{
    edges[++nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,w,head[v]);
    head[v]=nEdge;
}
int spfa(int s,int t,int cap)
{
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    cap*=10;
    d[s][cap]=0;
    queue<pair<int,int> >q;
    q.push(make_pair(s,cap));
    pair<int,int>pii;
    int u,st;
    while(!q.empty())
    {
        pii=q.front();q.pop();
        u=pii.first;st=pii.second;
        inq[u][st]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            int cost=edges[k].w;
            if(st>=cost&&d[v][st-cost]>d[u][st]+cost)
            {
                d[v][st-cost]=d[u][st]+cost;
                if(!inq[v][st-cost]) {inq[v][st-cost]=true;q.push(make_pair(v,st-cost));}
            }
            if(flag[u])
            {
                if(cap>=cost&&d[v][cap-cost]>d[u][st]+cost)
                {
                    d[v][cap-cost]=d[u][st]+cost;
                    if(!inq[v][cap-cost]) {inq[v][cap-cost]=true;q.push(make_pair(v,cap-cost));}
                }
            }
        }
    }
    int res=inf;
    for(int i=0;i<=cap;++i)
        res=min(res,d[t][i]);
    return res==inf?-1:res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char str[30],str2[30];
    int n,m,s,t,cap,N;
    while(~scanf("%d%d%d",&n,&m,&cap))
    {
        if(n==0&&m==0&&cap==0) break;
        mp.clear();
        N=0;
        scanf("%s",str);
        s=mp[(string)str]=++N;
        scanf("%s",str);
        t=mp[(string)str]=++N;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        memset(flag,0,sizeof(flag));
        int u,v,w;
        for(int i=0;i<n;++i)
        {
            scanf("%s%s%d",str,str2,&w);
            if(mp[(string)str]) u=mp[(string)str];
            else u=mp[(string)str]=++N;
            if(mp[(string)str2]) v=mp[(string)str2];
            else v=mp[(string)str2]=++N;
            AddEdges(u,v,w);
        }
        for(int i=0;i<m;++i)
        {
            scanf("%s",str);
            flag[mp[(string)str]]=true;
        }
        int ans=spfa(s,t,cap);
        printf("%d\n",ans);
    }
    return 0;
}

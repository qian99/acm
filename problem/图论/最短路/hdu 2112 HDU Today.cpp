#include <iostream>
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
const int maxn=150+10;
struct Edge
{
    int from,to,dist;
};
struct HeapNode
{
    int d,u;
    bool operator < (const HeapNode & a) const
    {
        return a.d<d;
    }
};
struct Dijkstra
{
    int n,m;
    vector<Edge>edges;
    vector<int>G[maxn];
    int d[maxn];
    bool vis[maxn];
    void clearAll()
    {
        for(int i=0;i<maxn;++i) G[i].clear();
        edges.clear();
    }
    void AddEdges(int from,int to,int dist)
    {
        edges.push_back((Edge){from,to,dist});
        edges.push_back((Edge){to,from,dist});
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    void dijkstra(int s,int n)
    {
        this->n=n;
        for(int i=0;i<=n;++i) d[i]=inf;
        memset(vis,0,sizeof(vis));
        d[s]=0;
        priority_queue<HeapNode>q;
        q.push((HeapNode){0,s});
        while(!q.empty())
        {
            HeapNode hp=q.top();q.pop();
            int u=hp.u;
            if(vis[u]) continue;
            vis[u]=true;
            for(int i=0;i<G[u].size();++i)
            {
                Edge e=edges[G[u][i]];
                if(d[e.to]>d[u]+e.dist)
                {
                    d[e.to]=d[u]+e.dist;
                    q.push((HeapNode){d[e.to],e.to});
                }
            }
        }
    }
}slover;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char s1[30],s2[30];
    int n;
    map<string,int>mp;
    while(~scanf("%d",&n))
    {
        if(n==-1) break;
        slover.clearAll();
        mp.clear();
        string str1,str2;
        int N=3,s=1,t=2,c;
        scanf("%s%s",s1,s2);
        if(strcmp(s1,s2)==0) t=s;
        mp[s1]=s;
        mp[s2]=t;
        for(int i=0;i<n;++i)
        {
            scanf("%s%s%d",s1,s2,&c);
            if(!mp[s1]) mp[s1]=N++;
            if(!mp[s2]) mp[s2]=N++;
            slover.AddEdges(mp[s1],mp[s2],c);
        }
        slover.dijkstra(s,N);
        int ans=slover.d[t];
        if(ans==inf) printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}

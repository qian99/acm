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
const int maxn=10000+10;
const int maxm=20000+10;
int parents[maxn],degree[maxn],p[maxn];
vector<int>G[maxn];
struct Edge
{
    int u,v,type;
    bool operator < (const Edge & a) const
    {
        return type<a.type;
    }
};
Edge edges[maxm];
void Init(int n)
{
    for(int i=0;i<=n;++i)
    {
        parents[i]=i;
        degree[i]=0;
        G[i].clear();
    }
}
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
void Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        parents[b]=a;
    }
}
int solve(int n)
{
    queue<int>q;
    int fa,res=1,cnt=0;
    int tmp=-1;
    for(int i=0;i<n;++i)
    {
        fa=Find(i);
        if(i==fa) cnt++;
        if(i==fa&&!degree[i])
        {
            if(tmp==-1) tmp=fa;
            if(i!=tmp) res=-1;
            q.push(i);
            p[i]=-1;
        }
    }
    int ed=-1;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=0;i<G[u].size();++i)
        {
            int v=Find(G[u][i]);
            degree[v]--;
            if(!degree[v])
            {
                q.push(v);
                p[v]=u;
                ed=v;
            }
        }
    }
    for(int i=0;i<n;++i)
      if(degree[i]) return 0;
    int sum=0;
    while(ed!=-1)
    {
        sum++;
        ed=p[ed];
    }
    if(sum!=cnt&&cnt!=1) res=-1;
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    char ss[2];
    while(~scanf("%d%d",&n,&m))
    {
        Init(n);
        int a,b,c;
        for(int i=0;i<m;++i)
        {
            scanf("%d %s %d",&a,ss,&b);
            if(ss[0]=='=') c=0;
            else if(ss[0]=='>') c=1;
            else c=2;
            edges[i]=(Edge){a,b,c};
        }
        sort(edges,edges+m);
        bool flag=true;
        for(int i=0;i<m;++i)
        {
            if(edges[i].type==0)
            {
                Uion(edges[i].u,edges[i].v);
                continue;
            }
            int x=Find(edges[i].u);
            int y=Find(edges[i].v);
            if(x==y) {flag=false;break;}
            if(edges[i].type==1)
            {
                G[x].push_back(y);
                degree[y]++;
            }
            else
            {
                G[y].push_back(x);
                degree[x]++;
            }
        }
        int ans=1;
        if(flag) ans=solve(n);
        if(!flag||ans==0) puts("CONFLICT");
        else if(ans==-1) puts("UNCERTAIN");
        else puts("OK");
    }
    return 0;
}

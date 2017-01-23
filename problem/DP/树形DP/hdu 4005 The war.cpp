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
const int maxn=10000+10;
const int maxm=100000+10;
struct Edge
{
    int v;
    int w;
    int next;
};
struct Node
{
    int u,v,w;
};
Edge edges[maxm<<1];
int head[maxn],pre[maxn],ebcno[maxn];
int n,m,nEdge,dfs_clock,ebc_cnt,ans;
stack<int>S;
vector<Node>brights;
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int tarjan(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        if(k!=(fa^1))
        {
            int v=edges[k].v;
            if(!pre[v])
            {
                int lowv=tarjan(v,k);
                lowu=min(lowu,lowv);
                if(lowv>pre[u])
                {
                    Node e;
                    e.u=u;e.v=v;e.w=edges[k].w;
                    brights.push_back(e);
                    ebc_cnt++;
                    while(true)
                    {
                        int x=S.top();S.pop();
                        ebcno[x]=ebc_cnt;
                        if(x==v) break;
                    }
                }
            }
            else if(pre[v]<lowu) lowu=pre[v];
        }
    }
    return lowu;
}
void find_ebc()
{
    memset(pre,0,sizeof(pre));
    brights.clear();
    dfs_clock=ebc_cnt=0;
    while(!S.empty()) S.pop();
    for(int i=1;i<=n;++i)
    {
        if(pre[i]) continue;
        tarjan(i,-1);
        if(!S.empty())
        {
            ebc_cnt++;
            while(!S.empty())
            {
                int x=S.top();S.pop();
                ebcno[x]=ebc_cnt;
            }
        }
    }

}
int dfs(int u,int fa)
{
    int minv=inf,min2=inf;//,mm=inf;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        int tmp=dfs(v,u);
        tmp=min(edges[k].w,tmp);
        if(tmp<minv)
        {
            min2=minv;
            minv=tmp;
        }
        else if(tmp<min2) min2=tmp;
    }
    ans=min(ans,min2);
    return minv;
}
void solve()
{
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    int s=-1,t=-1;
    int minw=inf;
    for(int i=0;i<brights.size();++i)
    {
        Node nd=brights[i];
        AddEdge(ebcno[nd.u],ebcno[nd.v],nd.w);
        AddEdge(ebcno[nd.v],ebcno[nd.u],nd.w);
        if(nd.w<minw)
        {
            minw=nd.w;;
            s=ebcno[nd.u];
            t=ebcno[nd.v];
        }
    }
    ans=inf;
    if(s==-1&&t==-1) return;
    dfs(s,t);
    dfs(t,s);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int a,b,c;
        while(m--)
        {
            scanf("%d%d%d",&a,&b,&c);
            AddEdge(a,b,c);
            AddEdge(b,a,c);
        }
        find_ebc();
        solve();
        if(ans==inf)
            puts("-1");
        else printf("%d\n",ans);
    }
    return 0;
}

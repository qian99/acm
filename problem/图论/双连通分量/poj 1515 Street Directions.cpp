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
const int maxm=10000+10;
struct Edge
{
    int v,next;
    Edge(){};
    Edge(int vv,int nx){v=vv;next=nx;}
}edges[maxm<<1];
int head[maxn],nEdge;
int pre[maxn],id[maxn],ebc_cnt,dfs_clock;
bool flag[maxm<<1];
stack<int>S;
void AddEdge(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
int tarjan(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(!pre[v])
        {
            int lowv=tarjan(v,u);
            lowu=min(lowu,lowv);
            if(lowv>pre[u])
            {
                printf("%d %d\n",u,v);
                printf("%d %d\n",v,u);
                flag[k]=flag[k^1]=true;
                ebc_cnt++;
                while(true)
                {
                    int x=S.top();S.pop();
                    id[x]=ebc_cnt;
                    if(x==v) break;
                }
            }
        }
        else if(pre[v]<lowu&&v!=fa)
            lowu=min(lowu,pre[v]);
        if(!flag[k]&&v!=fa)
        {
            flag[k]=flag[k^1]=true;
            printf("%d %d\n",u,v);
        }
    }
    return lowu;
}
void find_ebc(int n)
{
    memset(pre,0,sizeof(pre));
    memset(flag,0,sizeof(flag));
    memset(id,0,sizeof(id));
    while(!S.empty()) S.pop();
    dfs_clock=ebc_cnt=0;
    for(int i=1;i<=n;++i)
        if(!pre[i]) tarjan(i,-1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    int tcase=0;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        printf("%d\n\n",++tcase);
        int u,v;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
        }
        find_ebc(n);
        printf("#\n");
    }
    return 0;
}

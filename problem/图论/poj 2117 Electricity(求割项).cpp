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
    int v,next;
    Edge(){};
    Edge(int vv,int nx){v=vv;next=nx;}
}edges[maxm<<1];
int head[maxn],nEdge;
int pre[maxn],cnt[maxn],dfs_clock;
bool iscut[maxn];
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(pre,0,sizeof(pre));
    memset(iscut,0,sizeof(iscut));
    memset(cnt,0,sizeof(cnt));
    nEdge=-1;dfs_clock=0;
}
int tarjan(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    int childs=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        if(!pre[v])
        {
            childs++;
            int lowv=tarjan(v,u);
            lowu=min(lowu,lowv);
            if(lowv>=pre[u])
            {
                iscut[u]=true;
                cnt[u]++;
            }
        }
        else
            lowu=min(lowu,pre[v]);
    }
    if(fa==-1&&childs==1) {iscut[u]=false;cnt[u]=0;}
    if(iscut[u]&&fa!=-1) cnt[u]++;
    return lowu;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        Init();
        int u,v;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        int rnt=0,maxval=0;
        for(int i=0;i<n;++i)
        {
            if(!pre[i]) {tarjan(i,-1);rnt++;}
            maxval=max(maxval,cnt[i]-1);
        }
        if(n==1) rnt=maxval=0;
        if(m==0) rnt=n-1;
        printf("%d\n",rnt+maxval);
    }
    return 0;
}


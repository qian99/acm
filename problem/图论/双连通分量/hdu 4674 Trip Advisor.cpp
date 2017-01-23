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
const int maxn=100000+10;
struct Edge
{
    int u,v;
};
vector<int>G[maxn];
int pre[maxn],instack[maxn],bccno[maxn],dfs_clock,bcc_cnt;
int fa[maxn][22],d[maxn],vis[maxn];
Edge fap[maxn];
stack<int>S;
int n,m;
int tarjan(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    instack[u]=1;
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            int lowv=tarjan(v,u);
            lowu=min(lowu,lowv);
        }
        else if(instack[v]&&v!=fa)
           lowu=min(lowu,pre[v]);
    }
    if(lowu==pre[u])
    {
        ++bcc_cnt;
        while(true)
        {
            int x=S.top();S.pop();
            bccno[x]=bcc_cnt;
            instack[x]=0;
            if(x==u) break;
        }
    }
    return lowu;
}
void find_bcc()
{
    memset(pre,0,sizeof(pre));
    memset(instack,0,sizeof(instack));
    memset(bccno,0,sizeof(bccno));
    dfs_clock=bcc_cnt=0;
    tarjan(1,-1);
}
void bfs()
{
    memset(fa,0,sizeof(fa));
    memset(vis,0,sizeof(vis));
    d[bccno[1]]=1;
    queue<int>q;
    q.push(1);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=0;i<G[u].size();++i)
        {
            int v=G[u][i];
            if(!vis[v]&&bccno[u]!=bccno[v])
            {
                d[bccno[v]]=d[bccno[u]]+1;
                fa[bccno[v]][0]=bccno[u];
                fap[bccno[v]]=(Edge){v,u};
            }
            if(!vis[v]) q.push(v);
        }
    }
}
int ax,ay,tx,ty,ansp;
bool iss;
int lca(int x,int y)
{
    bool flag=false;
    if(d[x]>d[y]) flag=true,swap(x,y);
    ty=y;
    for(int i=20;i>=0;--i)
      if(d[fa[y][i]]>d[x]) y=fa[y][i];
    if(fa[y][0]==x)
    {
        ax=fap[y].v;ay=fap[ty].u;
        if(flag) swap(ax,ay);
        return x;
    }
    ax=fap[x].u;ay=fap[ty].u;
    if(d[y]>d[x]) y=fa[y][0];
    if(flag) swap(ax,ay);
    for(int i=20;i>=0;--i)
    {
        if(fa[x][i]!=fa[y][i])
        {
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    iss=fap[x].v==fap[y].v;
    ansp=fap[x].v;
    return fa[x][0];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        int a,b;
        for(int i=0;i<=n;++i) G[i].clear();
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            G[a].push_back(b);
            G[b].push_back(a);
        }
        find_bcc();
        bfs();
        for(int i=1;i<=20;++i)
           for(int j=1;j<=bcc_cnt;++j)
              fa[j][i]=fa[fa[j][i-1]][i-1];
        int q,x,y,p;
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d%d%d",&x,&y,&p);
            //printf("%d\n",lca(x,y));
            int cx=bccno[x],cy=bccno[y],cp=bccno[p];
            int ans=lca(cx,cy);
            if(x==y)    //x、y若相同，则p不等于x时无解
            {
                if(x==p) printf("Yes\n");
                else printf("No\n");
                continue;
            }
            if(cx==cy)   //若x、y在同一个环中，则p不在此环中时无解
            {
                if(cx==cp) printf("Yes\n");
                else printf("No\n");
                continue;
            }
            if(ax==x&&cx==cp&&x!=p)  //x与p在同一环中，并且x向y走一步就出环，并且x！=p，则无解
            {
                printf("No\n");
                continue;
            }
            if(ay==y&&cy==cp&&y!=p)  //y与p在同一环中，并且y向x走一步就出环，并且y！=p，则无解
            {
                printf("No\n");
                continue;
            }
            if(cp==cx||cp==cy)       //其余的x与p或者y与p在一个环中的一定有解
            {
                printf("Yes\n");
                continue;
            }
            if(d[cp]<d[ans])       //p不在x-y的路径上
            {
                printf("No\n");
                continue;
            }
            tx=cx;
            int inp,outp;
            for(int i=20;i>=0;--i) if(d[fa[tx][i]]>d[cp]) tx=fa[tx][i];
            if(fa[tx][0]!=cp)
            {
                ty=cy;
                for(int i=20;i>=0;--i) if(d[fa[ty][i]]>d[cp]) ty=fa[ty][i];
                if(fa[ty][0]!=cp)
                {
                    printf("No\n");
                    continue;
                }
                else inp=fap[ty].v,outp=fap[cp].u;
            }
            else inp=fap[tx].v,outp=fap[cp].u;
            if(ans==cp)
            {
                if(iss&&ansp!=p) printf("No\n");
                else printf("Yes\n"); continue;
            }
            if(inp==outp&&p!=inp) printf("No\n");
            else printf("Yes\n");
        }
    }
    return 0;
}

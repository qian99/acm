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
const int maxn=100000+10;
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],nEdge;
int S[maxn],dfs_clock,n;
bool flag[maxn];
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void Dfs(int u,int fa)
{
    S[dfs_clock++]=u;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        if(edges[k].v==fa) continue;
        Dfs(edges[k].v,u);
    }
    S[dfs_clock++]=u+n;
}
struct SplayTree
{
    int ch[maxn][2],pre[maxn],root;
    void Init()
    {
        ch[0][0]=ch[0][1]=pre[0]=0;
    }
    void NewNode(int &rt,int id,int fa)
    {
        rt=id;
        ch[rt][0]=ch[rt][1]=0;
        pre[rt]=fa;
    }
    void Rotate(int x,int kind)
    {
        int y=pre[x];
        ch[y][kind^1]=ch[x][kind];
        pre[ch[x][kind]]=y;
        if(pre[y]) ch[pre[y]][ch[pre[y]][1]==y]=x;
        ch[x][kind]=y;
        pre[x]=pre[y];
        pre[y]=x;
    }
    void Splay(int rt,int goal)
    {
        while(pre[rt]!=goal)
        {
            int y=pre[rt];
            if(pre[y]==goal)
                Rotate(rt,ch[y][0]==rt);
            else
            {
                int kind=ch[pre[y]][0]==y;
                if(ch[y][kind]==rt)
                {
                    Rotate(rt,kind^1);
                    Rotate(rt,kind);
                }
                else
                {
                    Rotate(y,kind);
                    Rotate(rt,kind);
                }
            }
        }
    }
    void build(int l,int r,int &rt,int fa)
    {
        if(l>r) return ;
        int m=(l+r)>>1;
        NewNode(rt,S[m],fa);
        build(l,m-1,ch[rt][0],rt);
        build(m+1,r,ch[rt][1],rt);
    }
    void Move(int x,int y)
    {
        if(x==y) return ;
        Splay(x,0);
        Splay(x+n,x);
        int ry=y;
        while(ry)
        {
            if(ry==ch[x+n][0]) return ;
            ry=pre[ry];
        }
        int rl=ch[x][0],rr=ch[x+n][1];
        ch[x][0]=ch[x+n][1]=0;
        pre[rl]=pre[rr]=0;
        if(rl&&rr)
        {
            while(ch[rl][1]) rl=ch[rl][1];
            ch[rl][1]=rr;
            pre[rr]=rl;
        }
        if(y==0) return ;
        Splay(y,0);
        Splay(y+n,y);
        if(ch[y+n][0]==0)
        {
            ch[y+n][0]=x;
            pre[x]=y+n;
        }
        else
        {
            int rc=ch[y+n][0];
            while(ch[rc][1]) rc=ch[rc][1];
            Splay(rc,y+n);
            ch[rc][1]=x;
            pre[x]=rc;
        }
    }
    int Query(int x)
    {
        Splay(x,0);
        while(ch[x][0]) x=ch[x][0];
        return x;
    }
}splay_tree;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    bool first=true;
    char str[10];
    while(~scanf("%d",&n))
    {
        if(!first) printf("\n");
        first=false;
        memset(head,0xff,sizeof(head));
        memset(flag,0,sizeof(flag));
        nEdge=-1;
        splay_tree.Init();
        int u;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&u);
            if(u) AddEdges(u,i);
            else flag[i]=true;
        }
        for(int i=1;i<=n;++i)
        {
            if(flag[i])
            {
                dfs_clock=0;
                Dfs(i,-1);
                splay_tree.build(0,dfs_clock-1,splay_tree.root,0);
            }
        }
        int q,x,y;
        scanf("%d",&q);
        while(q--)
        {
            scanf("%s",str);
            if(str[0]=='M')
            {
                scanf("%d%d",&x,&y);
                splay_tree.Move(x,y);
            }
            else
            {
                scanf("%d",&x);
                printf("%d\n",splay_tree.Query(x));
            }
        }
    }
    return 0;
}

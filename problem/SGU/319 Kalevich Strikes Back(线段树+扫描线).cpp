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
const int maxn=60000+10;
int pre[maxn],num[maxn<<1];
int head[maxn],nEdge;
ll area[maxn];
map<int,int>mp;
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxn<<1];
struct Line
{
    int y,L,R,id;
    Line(){}
    Line(int y,int L,int R,int id):y(y),L(L),R(R),id(id){}
    bool operator <(const Line & a) const
    {
        return y<a.y;
    }
}Lines[maxn<<1];
struct SegTree
{
    int cover[maxn<<3];
    void PushDown(int rt)
    {
        if(cover[rt]!=-1)
        {
            cover[rt<<1]=cover[rt<<1|1]=cover[rt];
            cover[rt]=-1;
        }
    }
    void build(int l,int r,int rt)
    {
        cover[rt]=0;
        if(l==r) return ;
        int m=(l+r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
    }
    int Query(int L,int R,int l,int r,int rt)
    {
        if(l>=L&&r<=R&&cover[rt]!=-1) return cover[rt];
        PushDown(rt);
        int m=(l+r)>>1;
        if(m>=R) return Query(L,R,l,m,rt<<1);
        else if(m<L) return Query(L,R,m+1,r,rt<<1|1);
        return Query(L,R,l,m,rt<<1);
    }
    void Update(int L,int R,int l,int r,int rt,int id)
    {
        if(l>=L&&r<=R)
        {
            if(id>0) cover[rt]=id;
            else cover[rt]=pre[-id];
            return ;
        }
        int m=(l+r)>>1;
        PushDown(rt);
        if(m>=L) Update(L,R,l,m,rt<<1,id);
        if(m<R) Update(L,R,m+1,r,rt<<1|1,id);
    }
}tree;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    memset(pre,0,sizeof(pre));
    mp.clear();
}
void dfs(int u)
{
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        area[u]-=area[v];
        dfs(v);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,N,tot=0;
    Init();
    int x1,x2,y1,y2,w,h;
    scanf("%d",&n);
    scanf("%d%d",&w,&h);
    area[0]=(ll)w*h;
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        if(x1>x2) swap(x1,x2);
        if(y1>y2) swap(y1,y2);
        area[i]=(ll)(x2-x1)*(y2-y1);
        num[tot]=x1;
        Lines[tot++]=Line(y1,x1,x2,i);
        num[tot]=x2;
        Lines[tot++]=Line(y2,x1,x2,-i);
    }
    sort(Lines,Lines+tot);
    num[tot++]=0;num[tot++]=w;
    sort(num,num+tot);
    N=unique(num,num+tot)-num;
    for(int i=0;i<N;++i)
        mp[num[i]]=i+1;
    tree.build(1,N,1);
    tot-=2;
    int L,R;
    for(int i=0;i<tot;++i)
    {
        L=mp[Lines[i].L];
        R=mp[Lines[i].R];
        if(Lines[i].id>0)
        {
            pre[Lines[i].id]=tree.Query(L,R,1,N,1);
            AddEdges(pre[Lines[i].id],Lines[i].id);
        }
        tree.Update(L,R,1,N,1,Lines[i].id);
    }
    dfs(0);
    sort(area,area+n+1);
    printf("%lld",area[0]);
    for(int i=1;i<=n;++i)
        printf(" %lld",area[i]);
    printf("\n");
    return 0;
}

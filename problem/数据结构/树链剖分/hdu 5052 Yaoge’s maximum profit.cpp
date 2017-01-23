#pragma comment(linker,"/STACK:100000000,100000000")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 50000 + 10;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxn<<1];
int d[maxn],pa[maxn],fp[maxn],vson[maxn],val[maxn];
int head[maxn],id[maxn],convert[maxn],nEdge,N;
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,head[v]);
    head[v] = nEdge;
}
int dfs(int u,int fa)
{
    int csum=1,cmax=0,me=-1;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        d[v]=d[u]+1;pa[v]=u;
        int cc=dfs(v,u);
        csum+=cc;
        if(cc>cmax) {cmax=cc;me=v;}
    }
    vson[u]=me;
    return csum;
}
void dfs2(int u,int fa)
{
    if(vson[u]!=-1)
    {
        id[u]=++N;
        convert[N] = u;
        if(fa==-1||vson[fa]!=u) fp[u]=u;
        else fp[u]=fp[fa];
        dfs2(vson[u],u);
    }
    else if(fa==-1||vson[fa]==u)
        id[u]=++N,convert[N] = u,fp[u]=(fa==-1)?u:fp[fa];
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa||v==vson[u]) continue;
        fp[v]=v;
        if(vson[v] == -1)
        {
            id[v] = ++N;
            convert[N] = v;
        }
        dfs2(v,u);
    }
}
struct SegTree
{
    ll maxv[maxn<<2],minv[maxn<<2],mxp[maxn<<2][2],addv[maxn<<2];
    void PushUp(int rt)
    {
        maxv[rt] = max(maxv[rt<<1],maxv[rt<<1|1]);
        minv[rt] = min(minv[rt<<1],minv[rt<<1|1]);
        mxp[rt][0] = max(mxp[rt<<1][0],mxp[rt<<1|1][0]);
        mxp[rt][0] = max(mxp[rt][0],maxv[rt<<1] - minv[rt<<1|1]);
        if(mxp[rt][0] < 0) mxp[rt][0] = 0;
        mxp[rt][1] = max(mxp[rt<<1][1],mxp[rt<<1|1][1]);
        mxp[rt][1] = max(mxp[rt][1],maxv[rt<<1|1] - minv[rt<<1]);
        if(mxp[rt][1] < 0) mxp[rt][1] = 0;
    }
    void PushDown(int rt)
    {
        if(addv[rt])
        {
            addv[rt<<1] += addv[rt];
            addv[rt<<1|1] += addv[rt];
            maxv[rt<<1] += addv[rt];
            maxv[rt<<1|1] += addv[rt];
            minv[rt<<1] += addv[rt];
            minv[rt<<1|1] += addv[rt];
            addv[rt] = 0;
        }
    }
    void build(int l,int r,int rt)
    {
        addv[rt] = 0;
        if(l == r)
        {
            maxv[rt] = minv[rt] = val[convert[l]];
            mxp[rt][0] = mxp[rt][1] = 0;
            return ;
        }
        int m = (l + r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
        PushUp(rt);
    }
    void Update(int L,int R,int l,int r,int rt,int v)
    {
        if(l >= L && r <= R)
        {
            addv[rt] += v;
            minv[rt] += v;
            maxv[rt] += v;
            return ;
        }
        PushDown(rt);
        int m = (l + r)>>1;
        if(m >= L) Update(L,R,l,m,rt<<1,v);
        if(m < R) Update(L,R,m+1,r,rt<<1|1,v);
        PushUp(rt);
    }
    ll Query(int L,int R,int l,int r,int rt,int type,ll & mx,ll & mn)
    {
        if(l >= L && r <= R)
        {
            mx = maxv[rt];
            mn = minv[rt];
            return mxp[rt][type];
        }
        PushDown(rt);
        int m = (l + r)>>1;
        if(m >= R) return Query(L,R,l,m,rt<<1,type,mx,mn);
        else if(m < L) return Query(L,R,m+1,r,rt<<1|1,type,mx,mn);
        else
        {
            ll r1,r2,m1,m2,n1,n2;
            r1 = Query(L,R,l,m,rt<<1,type,m1,n1);
            r2 = Query(L,R,m+1,r,rt<<1|1,type,m2,n2);
            mx = max(m1,m2);
            mn = min(n1,n2);
            if(type == 0)
            {
                r1 = max(r1,r2);
                r1 = max(r1,m1 - n2);
            }
            else
            {
                r1 = max(r1,r2);
                r1 = max(r1,m2 - n1);
            }
            if(r1 < 0) r1 = 0;
            return r1;
        }
    }
}tree;
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(d,0,sizeof(d));
    memset(vson,0xff,sizeof(vson));
    memset(id,0xff,sizeof(id));
    nEdge=-1;N=0;
}
void ADD(int x,int y,int c)
{
    while(fp[x]!=fp[y])
    {
        if(d[fp[x]]<d[fp[y]])
        {
            swap(x,y);
        }
        tree.Update(id[fp[x]],id[x],1,N,1,c);
        x=pa[fp[x]];
    }
    if(d[x]<d[y])
    {
        swap(x,y);
    }
    tree.Update(id[y],id[x],1,N,1,c);
}
ll getMaxp(int x,int y)
{
    //x -> y
    ll ans = 0,maxx,minx,maxy,miny,rx,ry;
    ll tmax,tmin,tr;
    rx = ry = 0;
    maxx = maxy = 0;
    minx = miny = Inf;
    while(fp[x] != fp[y])
    {
        if(d[fp[x]] < d[fp[y]])
        {
            tr = tree.Query(id[fp[y]],id[y],1,N,1,1,tmax,tmin);
            ry = max(ry,tr);
            ry = max(ry,maxy - tmin);
            maxy = max(maxy,tmax);
            miny = min(miny,tmin);
            ans = max(ans,ry);
            y = pa[fp[y]];
        }
        else
        {
            tr = tree.Query(id[fp[x]],id[x],1,N,1,0,tmax,tmin);
            rx = max(rx,tr);
            rx = max(rx,tmax - minx);
            maxx = max(maxx,tmax);
            minx = min(minx,tmin);
            ans = max(ans,rx);
            x = pa[fp[x]];
        }
    }
    if(d[x] < d[y])
    {
        if(id[x] > id[y]) while(true);
        tr = tree.Query(id[x],id[y],1,N,1,1,tmax,tmin);
        ans = max(ans,tr);
        ans = max(ans,maxy - tmin);
        maxy = max(maxy,tmax);
        miny = min(miny,tmin);
        ans = max(ans,maxy - minx);
    }
    else
    {
//        if(id[y] > id[x]) while(true);
        tr = tree.Query(id[y],id[x],1,N,1,0,tmax,tmin);
        ans = max(ans,tr);
        ans = max(ans,tmax - minx);
        maxx = max(maxx,tmax);
        minx = min(minx,tmin);
        ans = max(ans,maxy - minx);
    }
    return ans;
    ////////////////////////////
}
void reads(int & x)
{
    char c;
    bool neg=false;
    while(((c=getchar())<'0'||c>'9')&&c!='-');
    if(c=='-')
    {
        neg=true;
        while((c=getchar())<'0'||c>'9');
    }
    x=c-'0';
    while(c=getchar(),c>='0'&&c<='9') x=x*10+c-'0';
    if(neg) x=-x;
}
void outs(ll num)
{
     if(num<0)
     {
         putchar('-');
         num=-num;
     }
     int ans[20],top=0;
     while(num!=0)
     {
         ans[top++]=num%10;
         num/=10;
     }
     if(top==0)
     putchar('0');
     for(int i=top-1;i>=0;i--){
         char ch=ans[i]+'0';
         putchar(ch);
     }
     putchar('\n');
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        Init();
        int n,m,u,v,w;
        reads(n);
        for(int i = 1;i <= n;++i)
            reads(val[i]);
        for(int i = 1;i < n;++i)
        {
            reads(u);reads(v);
            AddEdges(u,v);
        }
        dfs(1,-1);
        dfs2(1,-1);
        tree.build(1,N,1);
        reads(m);
        ll ans;
        while(m--)
        {
            reads(u);reads(v);reads(w);
            ans = getMaxp(u,v);
            outs(ans);
            ADD(u,v,w);
        }
    }
    return 0;
}

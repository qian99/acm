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
const int maxn=500000+100;
const int N=20000+100;
const int M=60000+100;
int ch[maxn][2],val[maxn],counts[maxn],size[maxn],r[maxn];
int root[maxn],S[maxn],tot,tot2;
void NewNode(int &rt,int v)
{
    if(tot2) rt=S[tot2--];
    else rt=++tot;
    ch[rt][0]=ch[rt][1]=0;
    size[rt]=counts[rt]=1;
    val[rt]=v;r[rt]=rand();
}
inline void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+counts[rt];
}
void Rotate(int &x,int kind)
{
    int y=ch[x][kind^1];
    ch[x][kind^1]=ch[y][kind];
    ch[y][kind]=x;
    PushUp(x);PushUp(y);
    x=y;
}
void Insert(int &rt,int v)
{
    if(rt==0)
    {
        NewNode(rt,v);
        return ;
    }
    if(val[rt]==v)
        counts[rt]++;
    else
    {
        int kind=(v>val[rt]);
        Insert(ch[rt][kind],v);
        if(r[ch[rt][kind]]<r[rt])
            Rotate(rt,kind^1);
    }
    PushUp(rt);
}
void Remove(int &rt,int v)
{
    if(val[rt]==v)
    {
        if(counts[rt]>1)
            counts[rt]--;
        else if(!ch[rt][0]&&!ch[rt][1])
        {S[++tot2]=rt;rt=0;return;}
        else
        {
            int kind=r[ch[rt][0]]<r[ch[rt][1]];
            Rotate(rt,kind);
            Remove(rt,v);
        }
    }
    else Remove(ch[rt][v>val[rt]],v);
    PushUp(rt);
}
int select(int rt,int k)
{
    if(size[ch[rt][1]]>=k) return select(ch[rt][1],k);
    if(size[ch[rt][1]]+counts[rt]>=k) return val[rt];
    return select(ch[rt][0],k-(size[ch[rt][1]]+counts[rt]));
}
int pa[N],weight[N];
int Find(int x)
{
    return x==pa[x]?x:pa[x]=Find(pa[x]);
}
struct Command
{
    int type,x,v;
    Command(){}
    Command(int type,int x,int v):type(type),x(x),v(v){}
}commands[maxn];
struct Edge
{
    int u,v;
}edges[M];
bool removed[M];
void changes(int x,int v)
{
    int u=Find(x);
    Remove(root[u],weight[x]);
    Insert(root[u],v);
    weight[x]=v;
}
int query(int x,int k)
{
    if(k<=0) return 0;
    x=Find(x);
    if(size[root[x]]<k) return 0;
    return select(root[x],k);
}
void mergeto(int &x,int &y)
{
    if(x==0) return ;
    if(ch[x][0]) mergeto(ch[x][0],y);
    if(ch[x][1]) mergeto(ch[x][1],y);
    while(counts[x]>=1) {Insert(y,val[x]);counts[x]--;}
    S[++tot2]=x;
    x=0;
}
void add_edges(int u,int v)
{
    u=Find(u),v=Find(v);
    if(u==v) return ;
    if(size[root[u]]>size[root[v]])
        mergeto(root[v],root[u]),pa[v]=u;
    else
        mergeto(root[u],root[v]),pa[u]=v;
}
void Init()
{
    memset(root,0,sizeof(root));
    ch[0][1]=ch[0][0]=0;
    size[0]=counts[0]=0;
    val[0]=0;r[0]=(1LL<<31)-1;
    tot=tot2=0;
}
double solve(int n,int m)
{
    Init();
    memset(removed,0,sizeof(removed));
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&weight[i]);
        pa[i]=i;
    }
    for(int i=1;i<=m;++i)
        scanf("%d%d",&edges[i].u,&edges[i].v);
    char str[5];
    int type,x,v,q_cnt=0,q=0;
    ll sum=0;
    while(true)
    {
        scanf("%s",str);
        if(str[0]=='E') break;
        scanf("%d",&x);
        if(str[0]=='D')
            removed[x]=true,type=0;
        else
        {
            scanf("%d",&v);
            if(str[0]=='C')
            {
                swap(weight[x],v);
                type=2;
            }
            else type=1;
        }
        commands[q++]=Command(type,x,v);
    }
    for(int i=1;i<=n;++i)
        NewNode(root[i],weight[i]);
    for(int i=1;i<=m;++i)
        if(!removed[i]) add_edges(edges[i].u,edges[i].v);
    for(int i=q-1;i>=0;--i)
    {
        type=commands[i].type;x=commands[i].x;v=commands[i].v;
        if(type==0) add_edges(edges[x].u,edges[x].v);
        else if(type==1)
        {
            sum+=query(x,v);
            q_cnt++;
        }
        else changes(x,v);
    }
    return sum/(double)q_cnt;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,tcase=0;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        tcase++;
        double ans=solve(n,m);
        printf("Case %d: %.6lf\n",tcase,ans);
    }
    return 0;
}

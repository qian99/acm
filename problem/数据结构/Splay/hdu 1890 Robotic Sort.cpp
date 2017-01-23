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
const int maxn=100000+10;
int pre[maxn],ch[maxn][2],filp[maxn],id[maxn];
int minv[maxn],size[maxn],val[maxn],tot,root,n;
struct Node
{
    int num,pos;
    bool operator <(const Node &a) const
    {
        return (num==a.num&&pos<a.pos)||(num<a.num);
    }
}node[maxn];
void Newnode(int & rt,int fa,int v)
{
    rt=++tot;
    pre[rt]=fa;
    ch[rt][0]=ch[rt][1]=0;
    minv[rt]=val[rt]=v;
    size[rt]=1;filp[rt]=0;
}
void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+1;
    minv[rt]=min(minv[ch[rt][0]],minv[ch[rt][1]]);
    minv[rt]=min(minv[rt],val[rt]);
}
void PushDown(int rt)
{
    if(filp[rt])
    {
        filp[ch[rt][0]]^=1;
        filp[ch[rt][1]]^=1;
        swap(ch[rt][0],ch[rt][1]);
        filp[rt]=0;
    }
}
void Rotate(int x,int kind)
{
    int y=pre[x];
    PushDown(x);PushDown(y);
    ch[y][kind^1]=ch[x][kind];
    pre[ch[x][kind]]=y;
    if(pre[y])
        ch[pre[y]][ch[pre[y]][1]==y]=x;
    pre[x]=pre[y];
    ch[x][kind]=y;
    pre[y]=x;
    PushUp(y);
}
void Splay(int rt,int goal)
{
    PushDown(rt);
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
    PushUp(rt);
    if(goal==0) root=rt;
}
void RotateMin(int v,int goal)
{
    int rt=root;
    PushDown(rt);
    while(val[rt]!=v)
    {
        if(minv[ch[rt][0]]==v)
            rt=ch[rt][0];
        else
            rt=ch[rt][1];
        PushDown(rt);
    }
    Splay(rt,goal);
}
int getMax(int rt)
{
    PushDown(rt);
    while(ch[rt][1])
    {
        rt=ch[rt][1];
        PushDown(rt);
    }
    return rt;
}
void DelRoot()
{
    int rt=root;
    if(ch[rt][0]==0)
    {
        root=ch[rt][1];
        pre[root]=0;
        return;
    }
    int rm=getMax(ch[rt][0]);
    Splay(rm,rt);
    pre[rm]=pre[rt];
    ch[rm][1]=ch[rt][1];
    pre[ch[rt][1]]=rm;
    root=rm;
    PushUp(root);
}
void solve()
{
    int ans;
    for(int i=1;i<=n;++i)
    {
        if(i!=1) printf(" ");
        RotateMin(i,0);
        filp[ch[root][0]]^=1;
        ans=i+size[ch[root][0]];
        printf("%d",ans);
        DelRoot();
    }
    printf("\n");
}
void build(int l,int r,int &rt,int fa)
{
    if(l>r) return ;
    int m=(l+r)>>1;
    Newnode(rt,fa,id[m]);
    build(l,m-1,ch[rt][0],rt);
    build(m+1,r,ch[rt][1],rt);
    PushUp(rt);
}
void Init()
{
    for(int i=0;i<n;++i)
    {
        scanf("%d",&node[i].num);
        node[i].pos=i;
    }
    sort(node,node+n);
    int cnt=0;
    for(int i=0;i<n;++i)
        id[node[i].pos]=++cnt;
    tot=root=0;
    ch[0][0]=ch[0][1]=0;
    pre[0]=filp[0]=size[0]=0;
    minv[0]=val[0]=inf;
    build(0,n-1,root,0);
    PushUp(root);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        Init();
        solve();
    }
    return 0;
}


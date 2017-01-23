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
const int maxn=130000+10;
int pre[maxn],ch[maxn][2],size[maxn],val[maxn];
int filp[maxn],tot,root;
int n,q;
void Newnode(int &rt,int fa,int v)
{
    rt=++tot;
    pre[rt]=fa;
    ch[rt][0]=ch[rt][1]=0;
    val[rt]=v;
    size[rt]=1;
    filp[rt]=0;
}
inline void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+1;
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
void RotateTo(int k,int goal)
{
    int rt=root;
    PushDown(rt);
    while(k!=size[ch[rt][0]])
    {
        if(k<size[ch[rt][0]])
            rt=ch[rt][0];
        else
        {
            k-=(size[ch[rt][0]]+1);
            rt=ch[rt][1];
        }
        PushDown(rt);
    }
    Splay(rt,goal);
}

void trans(int l,int r)
{
    RotateTo(l-1,0);
    RotateTo(r+1,root);
    int x=ch[root][1];
    int rt=ch[x][0];
    PushDown(rt);
    filp[rt]^=1;
}
void build(int l,int r,int & rt,int fa)
{
    if(l>r) return ;
    int m=(l+r)>>1;
    Newnode(rt,fa,m);
    build(l,m-1,ch[rt][0],rt);
    build(m+1,r,ch[rt][1],rt);
    PushUp(rt);
}
void Init()
{
    pre[0]=ch[0][0]=ch[0][1]=0;
    size[0]=val[0]=filp[0]=0;
    tot=root=0;
    Newnode(root,0,0);
    Newnode(ch[root][1],root,0);
    build(1,n,ch[ch[root][1]][0],ch[root][1]);
    PushUp(ch[root][1]);
    PushUp(root);
}
void dfs(int rt)
{
    PushDown(rt);
    if(ch[rt][0]) dfs(ch[rt][0]);
    if(val[rt]) printf("%d ",val[rt]);
    if(ch[rt][1]) dfs(ch[rt][1]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&q);
    Init();
    int l,r;
    while(q--)
    {
        scanf("%d%d",&l,&r);
        trans(l,r);
    }
    dfs(root);
    printf("\n");
    return 0;
}


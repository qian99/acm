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
const int maxn=300000+10;
int pre[maxn],ch[maxn][2],size[maxn],filp[maxn],val[maxn];
int res[maxn],cnt,root,tot,n,m;
void NewNode(int &rt,int fa,int v)
{
    rt=++tot;
    pre[rt]=fa;
    filp[rt]=ch[rt][0]=ch[rt][1]=0;
    size[rt]=1;val[rt]=v;
}
void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+1;
}
void PushDown(int rt)
{
    if(filp[rt])
    {
        filp[ch[rt][0]]^=1;filp[ch[rt][1]]^=1;
        swap(ch[rt][0],ch[rt][1]);
        filp[rt]=0;
    }
}
void traval(int x)
{
    if(x)
    {
        PushDown(x);
        traval(ch[x][0]);
        printf("结点%2d:左儿子 %2d 右儿子 %2d 父节点 %2d size=%2d ,val=%2d, filp=%2d\n",x,ch[x][0],ch[x][1],pre[x],size[x],val[x],filp[x]);
        traval(ch[x][1]);
    }
}
void Debug()
{
    printf("%d\n",root);
    traval(root);
}
void Rotate(int x,int k)
{
    int y=pre[x];
    PushDown(x);PushDown(y);
    ch[y][k^1]=ch[x][k];
    pre[ch[x][k]]=y;
    if(pre[y]) ch[pre[y]][ch[pre[y]][1]==y]=x;
    ch[x][k]=y;
    pre[x]=pre[y];
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
    while(size[ch[rt][0]]!=k)
    {
        if(size[ch[rt][0]]>k)
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
void Cut(int L,int R,int pos)
{
    RotateTo(L-1,0);
    RotateTo(R+1,root);
    int rc=ch[ch[root][1]][0];
    ch[pre[rc]][0]=0;
    PushUp(pre[rc]);
    RotateTo(pos,0);
    RotateTo(pos+1,root);
    pre[rc]=ch[root][1];
    ch[pre[rc]][0]=rc;
    PushUp(pre[rc]);
}
void Filp(int L,int R)
{
    RotateTo(L-1,0);
    RotateTo(R+1,root);
    filp[ch[ch[root][1]][0]]^=1;
}
void build(int l,int r,int &rt,int fa)
{
    if(l>r) return ;
    int m=(l+r)>>1;
    NewNode(rt,fa,m);
    build(l,m-1,ch[rt][0],rt);
    build(m+1,r,ch[rt][1],rt);
    PushUp(rt);
}
void Init()
{
    pre[0]=ch[0][0]=ch[0][1]=0;
    val[0]=size[0]=filp[0]=0;
    root=tot=0;
    NewNode(root,0,0);
    NewNode(ch[root][1],root,0);
    build(1,n,ch[ch[root][1]][0],ch[root][1]);
    PushUp(ch[root][1]);
    PushUp(root);
}
void dfs(int rt)
{
    if(rt==0) return ;
    PushDown(rt);
    dfs(ch[rt][0]);
    res[cnt++]=val[rt];
    dfs(ch[rt][1]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char str[10];
    while(~scanf("%d%d",&n,&m))
    {
        if(n==-1&&m==-1) break;
        Init();
        cnt=0;
        int a,b,c;
        while(m--)
        {
            scanf("%s",str);
            scanf("%d%d",&a,&b);
            if(str[0]=='C')
            {
                scanf("%d",&c);
                Cut(a,b,c);
            }
            else Filp(a,b);
        }
        dfs(root);
        for(int i=1;i<=n;++i)
        {
            if(i!=1) printf(" ");
            printf("%d",res[i]);
        }
        printf("\n");
    }
    return 0;
}


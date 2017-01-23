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
int pre[maxn],ch[maxn][2],val[maxn],root,tot;
int size[maxn],add[maxn],num[maxn];
ll sum[maxn];
int n,q;
void Newnode(int & rt,int fa,int v)
{
    rt=++tot;
    pre[rt]=fa;
    val[rt]=v;
    sum[rt]=v;
    add[rt]=0;
    size[rt]=1;
    ch[rt][0]=ch[rt][1]=0;
}
void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+1;
    sum[rt]=sum[ch[rt][0]]+sum[ch[rt][1]]+val[rt];
}
void PushDown(int rt)
{
    if(add[rt])
    {
        val[rt]+=add[rt];
        add[ch[rt][0]]+=add[rt];
        add[ch[rt][1]]+=add[rt];
        sum[ch[rt][0]]+=(ll)add[rt]*size[ch[rt][0]];
        sum[ch[rt][1]]+=(ll)add[rt]*size[ch[rt][1]];
        add[rt]=0;
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
        if(pre[pre[rt]]==goal)
            Rotate(rt,ch[pre[rt]][0]==rt);
        else
        {
            int y=pre[rt];
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
ll Query(int l,int r)
{
    RotateTo(l-1,0);
    RotateTo(r+1,root);
    return sum[ch[ch[root][1]][0]];
}
void Update(int l,int r,int v)
{
    RotateTo(l-1,0);
    RotateTo(r+1,root);
    int tmp=ch[ch[root][1]][0];
    add[tmp]+=v;
    sum[tmp]+=(ll)size[tmp]*v;
}
void build(int l,int r,int & rt,int fa)
{
    if(l>r) return ;
    int m=(l+r)>>1;
    Newnode(rt,fa,num[m]);
    build(l,m-1,ch[rt][0],rt);
    build(m+1,r,ch[rt][1],rt);
    PushUp(rt);
}
void Init()
{
    for(int i=0;i<n;++i)
        scanf("%d",&num[i]);
    pre[0]=ch[0][0]=ch[0][1]=size[0]=0;
    sum[0]=add[0]=0;
    root=tot=0;
    Newnode(root,0,-1);
    Newnode(ch[root][1],root,-1);
    size[root]=2;
    build(0,n-1,ch[ch[root][1]][0],ch[root][1]);
    PushUp(ch[root][1]);
    PushUp(root);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int l,r,v;
    char str[5];
    scanf("%d%d",&n,&q);
    Init();
    while(q--)
    {
        scanf("%s",str);
        scanf("%d%d",&l,&r);
        if(str[0]=='Q')
            printf("%lld\n",Query(l,r));
        else
        {
            scanf("%d",&v);
            Update(l,r,v);
        }
    }
    return 0;
}


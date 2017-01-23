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
const int maxn=300000+10;
int ch[maxn][2],pre[maxn],size[maxn],val[maxn],st[maxn];
int gcdst[maxn][2],root,tot;
int num[200010],fs[200010];
int gcd(int a,int b)
{
    if(a==-1) return b;
    if(b==-1) return a;
    int c;
    while(b)
    {
        c=a%b;
        a=b;
        b=c;
    }
    return a;
}
void NewNode(int &rt,int fa,int v,int state)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=0;
    size[rt]=1;val[rt]=v;
    pre[rt]=fa;
    gcdst[rt][state]=v;gcdst[rt][state^1]=-1;
    st[rt]=state;
}
void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+1;
    gcdst[rt][0]=gcd(gcdst[ch[rt][0]][0],gcdst[ch[rt][1]][0]);
    gcdst[rt][1]=gcd(gcdst[ch[rt][0]][1],gcdst[ch[rt][1]][1]);
    gcdst[rt][st[rt]]=gcd(gcdst[rt][st[rt]],val[rt]);
}
void Rotate(int x,int kind)
{
    int y=pre[x];
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
    while(size[ch[rt][0]]!=k)
    {
        if(size[ch[rt][0]]>k)
            rt=ch[rt][0];
        else
        {
            k-=(size[ch[rt][0]]+1);
            rt=ch[rt][1];
        }
    }
    Splay(rt,goal);
}
void build(int l,int r,int &rt,int fa)
{
    if(l>r) return ;
    int m=(l+r)>>1;
    NewNode(rt,fa,num[m],fs[m]);
    build(l,m-1,ch[rt][0],rt);
    build(m+1,r,ch[rt][1],rt);
    PushUp(rt);
}
int Query(int L,int R,int state)
{
    RotateTo(L-1,0);
    RotateTo(R+1,root);
    return gcdst[ch[ch[root][1]][0]][state];
}
void Insert(int pos,int v,int state)
{
    RotateTo(pos,0);
    if(ch[root][0]==0)
    {
        NewNode(ch[root][0],root,v,state);
        PushUp(root);
        return ;
    }
    int rc=ch[root][0];
    while(ch[rc][1])
        rc=ch[rc][1];
    Splay(rc,root);
    NewNode(ch[rc][1],rc,v,state);
    PushUp(rc);
    PushUp(root);
}
void Delete(int pos)
{
    RotateTo(pos,0);
    if(ch[root][0]==0)
    {
        root=ch[root][1];
        pre[root]=0;
        return ;
    }
    int rc=ch[root][0];
    while(ch[rc][1]) rc=ch[rc][1];
    Splay(rc,root);
    int rt=ch[root][1];
    ch[rc][1]=rt;
    pre[rt]=rc;
    root=rc;
    pre[rc]=0;
    PushUp(root);
}
void Changes(int pos)
{
    RotateTo(pos,0);
    st[root]^=1;
    PushUp(root);
}
void Modify(int pos,int v)
{
    RotateTo(pos,0);
    val[root]=v;
    PushUp(root);
}
void Init(int n)
{
    for(int i=0;i<n;++i)
        scanf("%d%d",&num[i],&fs[i]);
    ch[0][0]=ch[0][1]=0;
    pre[0]=size[0]=0;val[0]=-1;
    gcdst[0][0]=gcdst[0][1]=-1;
    root=tot=0;
    NewNode(root,0,-1,0);
    NewNode(ch[root][1],root,-1,0);
    build(0,n-1,ch[ch[root][1]][0],ch[root][1]);
    PushUp(ch[root][1]);
    PushUp(root);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,q;
    char str[5];
    while(~scanf("%d%d",&n,&q))
    {
        Init(n);
        while(q--)
        {
            scanf("%s",str);
            int L,R,x,s;
            if(str[0]=='Q')
            {
                scanf("%d%d%d",&L,&R,&s);
                printf("%d\n",Query(L,R,s));
            }
            else if(str[0]=='I')
            {
                scanf("%d%d%d",&L,&x,&s);
                Insert(L+1,x,s);
            }
            else if(str[0]=='D')
            {
                scanf("%d",&L);
                Delete(L);
            }
            else if(str[0]=='R')
            {
                scanf("%d",&L);
                Changes(L);
            }
            else
            {
                scanf("%d%d",&L,&x);
                Modify(L,x);
            }
        }
    }
    return 0;
}


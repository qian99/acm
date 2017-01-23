#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
//#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200000+10;
int num[maxn],n,q;
struct Splay_Tree
{
int ch[maxn][2],pre[maxn],size[maxn],val[maxn];
int pmax[maxn],fmax[maxn],smax[maxn],sum[maxn];
int tot,root;
void Newnode(int & rt,int fa,int v)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=0;
    pre[rt]=fa;size[rt]=1;
    val[rt]=pmax[rt]=fmax[rt]=smax[rt]=sum[rt]=v;
}
inline void PushUp(int rt)
{
    int ls=ch[rt][0],rs=ch[rt][1];
    size[rt]=size[ls]+size[rs]+1;
    sum[rt]=sum[ls]+sum[rs]+val[rt];

    smax[rt]=max(smax[ls],smax[rs]);
    smax[rt]=max(smax[rt],val[rt]);
    smax[rt]=max(smax[rt],fmax[ls]+val[rt]);
    smax[rt]=max(smax[rt],val[rt]+pmax[rs]);
    smax[rt]=max(smax[rt],fmax[ls]+val[rt]+pmax[rs]);

    pmax[rt]=max(pmax[ls],sum[ls]+val[rt]);
    pmax[rt]=max(pmax[rt],sum[ls]+val[rt]+pmax[rs]);

    fmax[rt]=max(fmax[rs],sum[rs]+val[rt]);
    fmax[rt]=max(fmax[rt],sum[rs]+val[rt]+fmax[ls]);
}
void traval(int x)
{
    if(x)
    {
        traval(ch[x][0]);
        printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d ,val = %2d , smax = %2d \n",x,ch[x][0],ch[x][1],pre[x],size[x],val[x],smax[x]);
        traval(ch[x][1]);
    }
}
void debug()
{
    printf("root:%d\n",root);
    traval(root);
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
inline int getMax(int rt)
{
    while(ch[rt][1])
        rt=ch[rt][1];
    return rt;
}
void DelRoot()
{
    int rt=root;
    if(ch[rt][0]==0)
    {
        pre[ch[rt][1]]=0;
        root=ch[rt][1];
        return ;
    }
    int rm=getMax(ch[rt][0]);
    Splay(rm,rt);
    ch[rm][1]=ch[rt][1];
    pre[ch[rt][1]]=rm;
    pre[rm]=0;
    root=rm;
    PushUp(root);
}
void Insert(int x,int y)
{
    RotateTo(x,0);
    //debug();
    int rt=root;
    int nt;
    if(ch[rt][0]==0)
    {
        Newnode(nt,rt,y);
        ch[rt][0]=nt;
        PushUp(rt);
        return;
    }
    int rm=getMax(ch[rt][0]);
    Splay(rm,rt);
    Newnode(nt,rm,y);
    ch[rm][1]=nt;
    PushUp(rm);
    PushUp(rt);
}
void build(int l,int r,int &rt,int fa)
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
    ch[0][0]=ch[0][1]=0;
    pre[0]=size[0]=0;
    pmax[0]=fmax[0]=smax[0]=-inf;
    val[0]=sum[0]=0;
    tot=root=0;
    Newnode(root,0,0);
    Newnode(ch[root][1],root,0);
    build(1,n,ch[ch[root][1]][0],ch[root][1]);
    PushUp(ch[root][1]);
    PushUp(root);
}
}splay_tree;
char rchar()
{
    char res;
    while(res=getchar(),!isalpha(res));
    return res;
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
void outs(int num)
{
     if(num<0)
     {
         putchar('-');
         num=-num;
     }
     int ans[10],top=0;
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
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char c;
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;++i)
            reads(num[i]);
        splay_tree.Init();
        reads(q);
        int x,y;
        while(q--)
        {
            c=rchar();
            if(c=='I')
            {
                reads(x);reads(y);
                splay_tree.Insert(x,y);
            }
            else if(c=='D')
            {
                reads(x);
                splay_tree.RotateTo(x,0);
                splay_tree.DelRoot();
            }
            else if(c=='R')
            {
                reads(x);reads(y);
                splay_tree.RotateTo(x,0);
                splay_tree.val[splay_tree.root]=y;
                splay_tree.PushUp(splay_tree.root);
            }
            else
            {
                reads(x);reads(y);
                splay_tree.RotateTo(x-1,0);
                splay_tree.RotateTo(y+1,splay_tree.root);
                outs(splay_tree.smax[splay_tree.ch[splay_tree.ch[splay_tree.root][1]][0]]);
                //printf("%d\n",smax[ch[ch[root][1]][0]]);
            }
        }
    }
    return 0;
}


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
const int maxn=1024*1024*2+10;
int ch[maxn][2],pre[maxn],val[maxn],size[maxn],flip[maxn];
char str[maxn],s[20];
int root,tot;
void NewNode(int &rt,int fa,int v)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=0;
    pre[rt]=fa;val[rt]=v;
    size[rt]=1;flip[rt]=0;
}
inline void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+1;
}
inline void PushDown(int rt)
{
    if(flip[rt])
    {
        flip[ch[rt][0]]^=1;
        flip[ch[rt][1]]^=1;
        swap(ch[rt][0],ch[rt][1]);
        flip[rt]=0;
    }
}
void Rotate(int x,int kind)
{
    int y=pre[x];
    PushDown(x);PushDown(y);
    ch[y][kind^1]=ch[x][kind];
    pre[ch[x][kind]]=y;
    if(pre[y]) ch[pre[y]][ch[pre[y]][1]==y]=x;
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
void Insert(int k,int rc)
{
    RotateTo(k,0);
    RotateTo(k+1,root);
    int rt=ch[root][1];
    pre[rc]=rt;
    ch[rt][0]=rc;
    PushUp(rt);
    PushUp(root);
}
void build(int l,int r,int &rt,int fa)
{
    if(l>r) return ;
    int m=(l+r)>>1;
    NewNode(rt,fa,(int)str[m]);
    build(l,m-1,ch[rt][0],rt);
    build(m+1,r,ch[rt][1],rt);
    PushUp(rt);
}
void Del(int k,int len)
{
    RotateTo(k,0);
    RotateTo(k+len+1,root);
    int rt=ch[root][1];
    ch[rt][0]=0;
    PushUp(rt);
    PushUp(root);
}
void Filp(int k,int len)
{
    RotateTo(k,0);
    RotateTo(k+len+1,root);
    flip[ch[ch[root][1]][0]]^=1;
}
char Get(int k)
{
    RotateTo(k+1,0);
    return val[root];
}
void Init()
{
    ch[0][0]=ch[0][1]=size[0]=val[0]=0;
    pre[0]=flip[0]=root=tot=0;
    NewNode(root,0,0);
    NewNode(ch[root][1],root,0);
    PushUp(root);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        Init();
        int x,rc,pos=0;
        while(n--)
        {
            scanf("%s",s);
            if(s[0]=='M')
                scanf("%d",&pos);
            else if(s[0]=='I')
            {
                scanf("%d",&x);
                getchar();
                gets(str);
                build(0,x-1,rc,0);
                Insert(pos,rc);
            }
            else if(s[0]=='D')
            {
                scanf("%d",&x);
                Del(pos,x);
            }
            else if(s[0]=='R')
            {
                scanf("%d",&x);
                Filp(pos,x);
            }
            else if(s[0]=='G')
                printf("%c\n",Get(pos));
            else if(s[0]=='P')
                pos--;
            else pos++;
        }
    }
    return 0;
}


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
const int maxn=200000+1000;
int ch[maxn][2],pre[maxn],val[maxn],size[maxn],minv[maxn],flip[maxn];
int addv[maxn],num[maxn],root,tot;
char str[20];
void NewNode(int &rt,int fa,int v)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=flip[rt]=addv[rt]=0;
    pre[rt]=fa;val[rt]=minv[rt]=v;
    size[rt]=1;
}
inline void PushUp(int rt)
{
    size[rt]=size[ch[rt][0]]+size[ch[rt][1]]+1;
    minv[rt]=min(minv[ch[rt][0]],minv[ch[rt][1]]);
    minv[rt]=min(minv[rt],val[rt]);
}
inline void rev(int rt)
{
    if(!rt) return ;
    swap(ch[rt][0],ch[rt][1]);
    flip[rt]^=1;
}
inline void adv(int rt,int v)
{
    if(!rt) return ;
    val[rt]+=v;
    minv[rt]+=v;
    addv[rt]+=v;
}
inline void PushDown(int rt)
{
    if(flip[rt])
    {
        rev(ch[rt][0]);
        rev(ch[rt][1]);
        flip[rt]=0;
    }
    if(addv[rt])
    {
        adv(ch[rt][0],addv[rt]);
        adv(ch[rt][1],addv[rt]);
        addv[rt]=0;
    }
}
void Rotate(int x,int kind)
{
    int y=pre[x];
    PushDown(y);PushDown(x);
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
void ADD(int L,int R,int v)
{
    RotateTo(L-1,0);
    RotateTo(R+1,root);
    adv(ch[ch[root][1]][0],v);
    PushUp(ch[root][1]);
    PushUp(root);
}
void Flip(int L,int R)
{
    RotateTo(L-1,0);
    RotateTo(R+1,root);
    rev(ch[ch[root][1]][0]);
    PushUp(ch[root][1]);
    PushUp(root);
}
void Insert(int k,int v)
{
    RotateTo(k,0);
    RotateTo(k+1,root);
    NewNode(ch[ch[root][1]][0],ch[root][1],v);
    PushUp(ch[root][1]);
    PushUp(root);
}
void Delete(int k)
{
    RotateTo(k,0);
    if(ch[root][0]==0)
    {
        pre[ch[root][1]]=0;
        root=ch[root][1];
        return ;
    }
    int rc=ch[root][0];
    PushDown(rc);
    while(ch[rc][1])
    {
        PushDown(rc);
        rc=ch[rc][1];
    }
    Splay(rc,root);
    ch[rc][1]=ch[root][1];
    pre[ch[root][1]]=rc;
    pre[rc]=0;
    root=rc;
    PushUp(root);
}
void Revolve(int L,int R,int T)
{
    T%=(R-L+1);
    if(T<0) T+=(R-L+1);
    if(T==0) return ;
    int M=R-T;
    Flip(L,M);
    Flip(M+1,R);
    Flip(L,R);
}
int getMin(int L,int R)
{
    RotateTo(L-1,0);
    RotateTo(R+1,root);
    return minv[ch[ch[root][1]][0]];
}
void build(int l,int r,int &rt,int fa)
{
    if(l>r) return ;
    int m=(l+r)>>1;
    NewNode(rt,fa,num[m]);
    build(l,m-1,ch[rt][0],rt);
    build(m+1,r,ch[rt][1],rt);
    PushUp(rt);
}
void Init(int n)
{
    for(int i=0;i<n;++i)
        scanf("%d",&num[i]);
    ch[0][0]=ch[0][1]=pre[0]=flip[0]=addv[0]=0;
    size[0]=val[0]=0;minv[0]=inf;
    root=tot=0;
    NewNode(root,0,inf);
    NewNode(ch[root][1],root,inf);
    build(0,n-1,ch[ch[root][1]][0],ch[root][1]);
    PushUp(ch[root][1]);
    PushUp(root);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,L,R,v;
    while(~scanf("%d",&n))
    {
        Init(n);
        scanf("%d",&m);
        while(m--)
        {
            scanf("%s",str);
            if(str[0]=='A')
            {
                scanf("%d%d%d",&L,&R,&v);
                ADD(L,R,v);
            }
            else if(str[0]=='R'&&str[3]=='E')
            {
                scanf("%d%d",&L,&R);
                Flip(L,R);
            }
            else if(str[0]=='R'&&str[3]=='O')
            {
                scanf("%d%d%d",&L,&R,&v);
                Revolve(L,R,v);
            }
            else if(str[0]=='I')
            {
                scanf("%d%d",&L,&v);
                Insert(L,v);
            }
            else if(str[0]=='D')
            {
                scanf("%d",&L);
                Delete(L);
            }
            else
            {
                scanf("%d%d",&L,&R);
                printf("%d\n",getMin(L,R));
            }
        }
    }
    return 0;
}

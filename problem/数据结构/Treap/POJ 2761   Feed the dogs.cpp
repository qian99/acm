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
const int maxn=100000+10;
int ch[maxn][2],r[maxn],val[maxn],size[maxn],counts[maxn];
int root,tot;
inline void Newnode(int &rt,int v)
{
    rt=++tot;
    ch[rt][0]=ch[rt][1]=0;
    r[rt]=rand();val[rt]=v;
    counts[rt]=size[rt]=1;
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
        Newnode(rt,v);
        return;
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
void remove(int &rt,int v)
{
    if(val[rt]==v)
    {
        if(counts[rt]>1)
            counts[rt]--;
        else if(!ch[rt][0]&&!ch[rt][1])
        {rt=0;return ;}
        else
        {
            int kind=r[ch[rt][0]]<r[ch[rt][1]];
            Rotate(rt,kind);
            remove(rt,v);
        }
    }
    else remove(ch[rt][v>val[rt]],v);
    PushUp(rt);
}
int select(int rt,int k)
{
    if(size[ch[rt][0]]>=k) return select(ch[rt][0],k);
    if(size[ch[rt][0]]+counts[rt]>=k) return val[rt];
    return select(ch[rt][1],k-size[ch[rt][0]]-counts[rt]);
}
void Init()
{
    ch[0][0]=ch[0][1]=0;
    size[0]=counts[0]=0;
    r[0]=(1LL<<31)-1;
    root=tot=0;
}
struct Node
{
    int l,r,k,id;
    Node(){}
    Node(int l,int r,int k,int id):l(l),r(r),k(k),id(id){}
    bool operator <(const Node & a) const
    {
        return (l==a.l&&r<a.r)||(l<a.l);
    }
}node[maxn>>1];
int num[maxn],ans[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    Init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%d",&num[i]);
    int l,r,k;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&l,&r,&k);
        node[i]=Node(l,r,k,i);
    }
    sort(node,node+m);
    l=1,r=0;
    for(int i=0;i<m;++i)
    {
        while(r<node[i].r)
            Insert(root,num[++r]);
        while(l<node[i].l)
            remove(root,num[l++]);
        ans[node[i].id]=select(root,node[i].k);
    }
    for(int i=0;i<m;++i)
        printf("%d\n",ans[i]);
    return 0;
}

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
const int maxm=300000+10;
struct Node
{
    int v,l,r,type;
    Node(){};
    Node(int vv,int xl,int xr,int tt) {v=vv;l=xl;r=xr;type=tt;}
    bool operator <(const Node &a)const
    {
        return (v==a.v&&type<a.type)||(v<a.v);
    }
}node[maxn<<1];
int val[maxn],vl[maxn],vr[maxn];
int maxv[maxm<<2],addv[maxm<<2],maxp[maxm<<2];
inline void PushUp(int rt)
{
    if(maxv[rt<<1]>maxv[rt<<1|1])
    {
        maxv[rt]=maxv[rt<<1];
        maxp[rt]=maxp[rt<<1];
    }
    else
    {
        maxv[rt]=maxv[rt<<1|1];
        maxp[rt]=maxp[rt<<1|1];
    }
}
void PushDown(int rt)
{
    if(addv[rt])
    {
        maxv[rt<<1]+=addv[rt];
        maxv[rt<<1|1]+=addv[rt];
        addv[rt<<1]+=addv[rt];
        addv[rt<<1|1]+=addv[rt];
        addv[rt]=0;
    }
}
void build(int l,int r,int rt)
{
    maxv[rt]=addv[rt]=0;
    if(l==r){maxp[rt]=l;return ;}
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l>=L&&r<=R)
    {
        maxv[rt]+=v;
        addv[rt]+=v;
        return ;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=L) Update(L,R,l,m,rt<<1,v);
    if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt,int &pos)
{
    if(l>=L&&r<=R)
    {
        pos=maxp[rt];
        return maxv[rt];
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=R) return Query(L,R,l,m,rt<<1,pos);
    else if(m<L) return Query(L,R,m+1,r,rt<<1|1,pos);
    else
    {
        int mx1,p1,mx2,p2;
        mx1=Query(L,R,l,m,rt<<1,p1);
        mx2=Query(L,R,m+1,r,rt<<1|1,p2);
        if(mx1<mx2)
        {
            mx1=mx2;
            p1=p2;
        }
        pos=p1;
        return mx1;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,tot=0,N=300000;
    scanf("%d",&n);
    build(1,N,1);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&vl[i],&val[i],&vr[i]);
        node[tot++]=Node(vl[i],val[i],vr[i],0);
        node[tot++]=Node(val[i],val[i],vr[i],1);
    }
    sort(node,node+tot);
    int maxnum=0,L,R;
    for(int i=0;i<tot;++i)
    {
        if(node[i].type)
            Update(node[i].l,node[i].r,1,N,1,-1);
        else
        {
            Update(node[i].l,node[i].r,1,N,1,1);
            int tmp,pos;
            tmp=Query(node[i].l,node[i].r,1,N,1,pos);
            if(tmp>maxnum)
            {
                maxnum=tmp;
                L=node[i].v;
                R=pos;
            }
        }
    }
    printf("%d\n",maxnum);
    bool first=true;
    for(int i=1;i<=n;++i)
    {
        if(val[i]>=L&&val[i]<=R&&vl[i]<=L&&vr[i]>=R)
        {
            if(!first) printf(" ");
            first=false;
            printf("%d",i);
        }
    }
    printf("\n");
    return 0;
}

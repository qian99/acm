#include<iostream>
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
const int N=100000;
int maxseg[maxn<<2],tosum[maxn<<2],maxup[maxn<<2],addv[maxn<<2];
int num[maxn],ans[maxn],pre[maxn*2];
struct Node
{
    int l,pos;
};
vector<Node>querys[maxn];
void PushUp(int rt)
{
    maxseg[rt]=max(maxseg[rt<<1],maxseg[rt<<1|1]);
    tosum[rt]=max(tosum[rt<<1],tosum[rt<<1|1]);
}
void PushDown(int rt)
{
    int ls=rt<<1,rs=rt<<1|1;
    maxup[ls]=max(maxup[ls],maxup[rt]+addv[ls]);
    maxup[rs]=max(maxup[rs],maxup[rt]+addv[rs]);
    maxseg[ls]=max(maxseg[ls],tosum[ls]+maxup[rt]);
    maxseg[rs]=max(maxseg[rs],tosum[rs]+maxup[rt]);
    addv[ls]+=addv[rt];addv[rs]+=addv[rt];
    tosum[ls]+=addv[rt];tosum[rs]+=addv[rt];
    addv[rt]=maxup[rt]=0;
}
void build(int l,int r,int rt)
{
    maxseg[rt]=tosum[rt]=addv[rt]=maxup[rt]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l>=L&&r<=R)
    {
        maxup[rt]=max(maxup[rt],addv[rt]+v);
        maxseg[rt]=max(maxseg[rt],tosum[rt]+v);
        addv[rt]+=v;tosum[rt]+=v;
        return;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=L)
     Update(L,R,l,m,rt<<1,v);
    if(m<R)
     Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R) return maxseg[rt];
    PushDown(rt);
    int m=(l+r)>>1;
    int res=0;
    if(m>=L)
     res=max(res,Query(L,R,l,m,rt<<1));
    if(m<R)
     res=max(res,Query(L,R,m+1,r,rt<<1|1));
    return res;
}
void solve(int n)
{
    memset(pre,0xff,sizeof(pre));
    int l,sz;
    Node tmp;
    for(int i=1;i<=n;++i)
    {
        if(pre[num[i]+N]==-1)
          l=1;
        else
          l=pre[num[i]+N]+1;
        pre[num[i]+N]=i;
        Update(l,i,1,n,1,num[i]);
        sz=querys[i].size();
        for(int j=0;j<sz;++j)
        {
            tmp=querys[i][j];
            ans[tmp.pos]=Query(tmp.l,i,1,n,1);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,q;
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&num[i]);
            querys[i].clear();
        }
        build(1,n,1);
        scanf("%d",&q);
        int l,r;
        Node tmp;
        for(int i=0;i<q;++i)
        {
            scanf("%d%d",&l,&r);
            tmp.l=l;tmp.pos=i;
            querys[r].push_back(tmp);
        }
        solve(n);
        for(int i=0;i<q;++i)
          printf("%d\n",ans[i]);
    }
    return 0;
}

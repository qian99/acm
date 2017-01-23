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
vector<int>G[maxn];
struct Node
{
    int l,pos;
};
vector<Node>querys[maxn];
int num[maxn],ans[maxn],n;
int maxv[maxn<<2],last[maxn];
inline void PushUp(int rt)
{
    maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
}
void build(int l,int r,int rt)
{
    maxv[rt]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        return maxv[rt];
    }
    int m=(l+r)>>1;
    if(m>=R)
      return Query(L,R,l,m,rt<<1);
    else if(m<L)
      return Query(L,R,m+1,r,rt<<1|1);
    return max(Query(L,R,l,m,rt<<1),Query(L,R,m+1,r,rt<<1|1));
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l==r)
    {
        maxv[rt]=max(maxv[rt],v);
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p)
     Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
void solve()
{
    memset(last,0xff,sizeof(last));
    build(1,n,1);
    int sz,l,r,z;
    Node tmp;
    for(int i=1;i<=n;++i)
    {
        sz=G[num[i]].size();
        for(int j=0;j<sz;++j)
        {
            z=G[num[i]][j];
            if(last[z]==-1)
              last[z]=i;
            else
            {
                Update(last[z],1,n,1,z);
                last[z]=i;
            }
        }
        sz=querys[i].size();
        for(int j=0;j<sz;++j)
        {
            tmp=querys[i][j];
            l=tmp.l;r=i;
            ans[tmp.pos]=Query(l,r,1,n,1);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    for(int i=1;i<maxn;++i)
      for(int j=i;j<maxn;j+=i)
        G[j].push_back(i);
    int t,q;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
          scanf("%d",&num[i]);
        for(int i=1;i<=n;++i)
          querys[i].clear();
        scanf("%d",&q);
        Node tmp;
        int l,r;
        for(int i=0;i<q;++i)
        {
            scanf("%d%d",&l,&r);
            tmp.l=l;tmp.pos=i;
            querys[r].push_back(tmp);
        }
        solve();
        for(int i=0;i<q;++i)
          printf("%d\n",ans[i]);
    }
    return 0;
}

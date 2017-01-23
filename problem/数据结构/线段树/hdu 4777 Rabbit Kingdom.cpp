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
const int maxn=200000+10;
int pre[maxn],num[maxn],ans[maxn];
int lf[maxn],rn[maxn];
int sum[maxn<<2];
int n,m;
struct Node
{
    int l,pos;
    bool operator <(const Node &a) const
    {
        return l>a.l;
    }
};
vector<int>vt[maxn];
vector<Node>querys[maxn];
inline void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
    sum[rt]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l==r)
    {
        sum[rt]+=v;
        return ;
    }
    int m=(l+r)>>1;
    if(p<=m) Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        return sum[rt];
    }
    int s=0;
    int m=(l+r)>>1;
    if(m>=L)
      s+=Query(L,R,l,m,rt<<1);
    if(m<R)
      s+=Query(L,R,m+1,r,rt<<1|1);
    return s;
}
void solve()
{
    memset(pre,0xff,sizeof(pre));
    int sz,ntmp,pp;
    for(int i=1;i<=n;++i)
    {
        sz=vt[num[i]].size();
        pp=1;
        for(int j=0;j<sz;++j)
        {
            ntmp=vt[num[i]][j];
            if(pre[ntmp]!=-1) pp=max(pp,pre[ntmp]+1);
            pre[ntmp]=i;
        }
        lf[i]=pp;
    }
    memset(pre,0xff,sizeof(pre));
    for(int i=n;i>=1;--i)
    {
        sz=vt[num[i]].size();
        pp=n;
        for(int j=0;j<sz;++j)
        {
            ntmp=vt[num[i]][j];
            if(pre[ntmp]!=-1) pp=min(pp,pre[ntmp]-1);
            pre[ntmp]=i;
        }
        rn[i]=pp;
    }
    Node node,tmp;
    priority_queue<Node>q;
    int x,y;
    for(int i=1;i<=n;++i)
    {
        Update(i,1,n,1,1);
        x=lf[i]-1;
        if(x) Update(x,1,n,1,-1);
        while(!q.empty())
        {
            tmp=q.top();
            if(tmp.l==i)
            {
                q.pop();
                Update(tmp.pos,1,n,1,-1);
                x=lf[tmp.pos]-1;
                if(x) Update(x,1,n,1,1);
            }
            else break;
        }
        y=rn[i]+1;
        if(y<=n)
        {
            tmp.l=y;tmp.pos=i;
            q.push(tmp);
        }
        sz=querys[i].size();
        for(int j=0;j<sz;++j)
        {
            node=querys[i][j];
            ans[node.pos]=Query(node.l,i,1,n,1);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    for(int i=2;i<=200000;++i)
      for(int j=i;j<=200000;j+=i)
        vt[j].push_back(i);
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        for(int i=1;i<=n;++i)
          scanf("%d",&num[i]);
        build(1,n,1);
        for(int i=0;i<=n;++i) querys[i].clear();
        int l,r;
        Node tmp;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&l,&r);
            tmp.l=l;tmp.pos=i;
            querys[r].push_back(tmp);
        }
        solve();
        for(int i=0;i<m;++i)
          printf("%d\n",ans[i]);
    }
    return 0;
}

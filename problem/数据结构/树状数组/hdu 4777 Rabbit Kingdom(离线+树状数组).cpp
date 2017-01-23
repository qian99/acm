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
int sum[maxn];
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
int lowbit(int x)
{
    return x&-x;
}
int Query(int x)
{
    int ret=0;
    while(x>0)
    {
        ret+=sum[x];
        x-=lowbit(x);
    }
    return ret;
}
void add(int x,int v)
{
    while(x<=n)
    {
        sum[x]+=v;
        x+=lowbit(x);
    }
}
void solve()
{
    memset(pre,0xff,sizeof(pre));
    memset(sum,0,sizeof(sum));
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
    int x,y;
    priority_queue<Node>q;
    for(int i=1;i<=n;++i)
    {
        add(i,1);
        x=lf[i]-1;
        if(x) add(x,-1);
        while(!q.empty())
        {
            tmp=q.top();
            if(tmp.l==i)
            {
                q.pop();
                add(tmp.pos,-1);
                x=lf[tmp.pos]-1;
                if(x) add(x,1);
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
            ans[node.pos]=Query(i)-Query(node.l-1);
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

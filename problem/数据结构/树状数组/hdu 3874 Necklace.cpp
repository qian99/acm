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
const int maxn=50000+10;
const int maxm=200000+10;
struct Node
{
    int l,pos;
};
ll C[maxn],ans[maxm];
int val[maxn],pre[1000010];
vector<Node>querys[maxn];
int n,m;
inline int lowbit(int x)
{
    return x&(-x);
}
void add(int x,ll v)
{
    while(x<=n)
    {
        C[x]+=v;
        x+=lowbit(x);
    }
}
ll sum(int x)
{
    ll ret=0;
    while(x>0)
    {
        ret+=C[x];
        x-=lowbit(x);
    }
    return ret;
}
void solve()
{
    int sz;
    Node tmp;
    memset(pre,0xff,sizeof(pre));
    memset(C,0,sizeof(C));
    for(int i=1;i<=n;++i)
    {
        if(pre[val[i]]!=-1)
          add(pre[val[i]],-val[i]);
        pre[val[i]]=i;
        add(i,val[i]);
        sz=querys[i].size();
        for(int j=0;j<sz;++j)
        {
            tmp=querys[i][j];
            ans[tmp.pos]=sum(i)-sum(tmp.l-1);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&val[i]);
            querys[i].clear();
        }
        Node tmp;
        int r;
        scanf("%d",&m);
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&tmp.l,&r);
            tmp.pos=i;
            querys[r].push_back(tmp);
        }
        solve();
        for(int i=0;i<m;++i)
          printf("%I64d\n",ans[i]);
    }
    return 0;
}

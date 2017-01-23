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
const int maxn=30000+10;
int pre[1000010];
int num[maxn],C[maxn],ans[200010],n;
struct Node
{
    int l,pos;
};
vector<Node>querys[maxn];
int lowbit(int x)
{
    return x&(-x);
}
int sum(int x)
{
    int ret=0;
    while(x>0)
    {
        ret+=C[x];
        x-=lowbit(x);
    }
    return ret;
}
void add(int x,int v)
{
   while(x<=n)
   {
       C[x]+=v;
       x+=lowbit(x);
   }
}
void solve()
{
    int sz;
    Node tmp;
    for(int i=1;i<=n;++i)
    {
        if(pre[num[i]]!=-1)
           add(pre[num[i]],-1);
        pre[num[i]]=i;
        add(i,1);
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
    while(~scanf("%d",&n))
    {
        memset(C,0,sizeof(C));
        memset(pre,0xff,sizeof(pre));
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&num[i]);
            querys[i].clear();
        }
        int q,l,r;
        Node tmp;
        scanf("%d",&q);
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

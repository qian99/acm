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
const int maxn=500+10;
struct Customer
{
    int time;
    int lx,ly,rx,ry;
}cust[maxn];
vector<int>G[maxn];
int link[maxn];
bool used[maxn];
bool check(Customer a,Customer b)
{
    return a.time+abs(a.ry-a.ly)+abs(a.rx-a.lx)+abs(a.ry-b.ly)+abs(a.rx-b.lx)<b.time;
}
bool dfs(int u)
{
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!used[v])
        {
            used[v]=true;
            if(link[v]==-1||dfs(link[v]))
            {
                link[v]=u;
                return true;
            }
        }
    }
    return false;
}
int hungary(int n)
{
    int res=0;
    memset(link,0xff,sizeof(link));
    for(int i=1;i<=n;++i)
    {
        memset(used,0,sizeof(used));
        if(dfs(i)) res++;
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    int m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&m);
        int hh,mm;
        for(int i=1;i<=m;++i)
        {
            scanf("%d:%d%d%d%d%d",&hh,&mm,&cust[i].lx,&cust[i].ly,&cust[i].rx,&cust[i].ry);
            cust[i].time=hh*60+mm;
        }
        for(int i=0;i<=m;++i) G[i].clear();
        for(int i=1;i<=m;++i)
        {
            for(int j=i+1;j<=m;++j)
            {
                if(check(cust[i],cust[j]))
                   G[i].push_back(j);
            }
        }
        int ans=m-hungary(m);
        printf("%d\n",ans);
    }
    return 0;
}

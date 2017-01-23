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
const int maxn=20000+10;
int pre[maxn],dfs_clock;
bool ins[maxn];
vector<int>G[maxn];
bool flag;
int tarjan(int u)
{
    int lowu=pre[u]=++dfs_clock;
    ins[u]=true;
    int cnt=0;
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            int lowv=tarjan(v);
            lowu=min(lowv,lowu);
            if(lowv>pre[u]) flag=false;
            if(lowv<pre[u]) cnt++;
        }
        else if(ins[v])
           lowu=min(lowu,pre[v]);
        else flag=false;
    }
    if(cnt>2) flag=false;
    ins[u]=false;
    return lowu;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<=n;++i) G[i].clear();
        int a,b;
        while(~scanf("%d%d",&a,&b))
        {
            if(a==0&&b==0) break;
            G[a].push_back(b);
        }
        memset(pre,0,sizeof(pre));
        memset(ins,0,sizeof(ins));
        flag=true;
        dfs_clock=0;
        tarjan(0);
        if(flag) puts("YES");
        else puts("NO");
    }
    return 0;
}

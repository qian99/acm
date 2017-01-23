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
const int maxn=100+10;
vector<int>G[maxn];
int link[maxn];
bool used[maxn];
struct Edge
{
    int u,v;
}edge[maxn*maxn];
bool dfs(int u,int a,int b)
{
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(u==a&&v==b) continue;
        if(!used[v])
        {
            used[v]=true;
            if(link[v]==-1||dfs(link[v],a,b))
            {
                link[v]=u;
                return true;
            }
        }
    }
    return false;
}
int hungary(int n,int a,int b)
{
    int res=0;
    memset(link,0xff,sizeof(link));
    for(int i=1;i<=n;++i)
    {
        memset(used,0,sizeof(used));
        if(dfs(i,a,b)) res++;
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,k;
    int tcase=0;
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        tcase++;
        for(int i=0;i<=n;++i) G[i].clear();
        int a,b;
        for(int i=0;i<k;++i)
        {
            scanf("%d%d",&a,&b);
            G[a].push_back(b);
            edge[i]=(Edge){a,b};
        }
        int ans=hungary(n,-1,-1);
        int sum=0;
        for(int i=0;i<k;++i)
        {
            if(ans!=hungary(n,edge[i].u,edge[i].v))
                sum++;
        }
        printf("Board %d have %d important blanks for %d chessmen.\n",tcase,sum,ans);
    }
    return 0;
}

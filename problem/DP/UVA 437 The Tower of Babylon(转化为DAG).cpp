#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100 + 10;
struct Node
{
    int x,y,z;
    void ajust()
    {
        if(x > y) swap(x,y);
        if(y > z) swap(y,z);
        if(x > y) swap(x,y);
    }
}node[maxn];
vector<int>G[maxn];
int dp[maxn],w[maxn];
bool check(int s1,int d1,int s2,int d2)
{
    int a,b,A,B;
    if(d1 == 0) a = node[s1].y,b = node[s1].z;
    else if(d1 == 1) a = node[s1].x,b = node[s1].z;
    else a = node[s1].x,b = node[s1].y;
    if(d2 == 0) A = node[s2].y,B = node[s2].z;
    else if(d2 == 1) A = node[s2].x,B = node[s2].z;
    else A = node[s2].x,B = node[s2].y;
    return a > A && b > B;
}
void dfs(int u)
{
    if(dp[u] != -1) return ;
    dp[u] = w[u];
    for(int i = 0;i < (int)G[u].size();++i)
    {
        int v = G[u][i];
        dfs(v);
        dp[u] = max(dp[u],dp[v] + w[u]);
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,tcase = 0;
    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        for(int i = 0;i < maxn; ++i) G[i].clear();
        for(int i = 0;i < n;++i)
        {
            scanf("%d%d%d",&node[i].x,&node[i].y,&node[i].z);
            node[i].ajust();
            w[i*3] = node[i].x;
            w[i*3+1] = node[i].y;
            w[i*3+2] = node[i].z;
        }
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
                for(int k = 0;k < 3;++k)
                    for(int l = 0;l < 3;++l)
                    {
                        if(check(i,k,j,l))
                            G[i*3+k].push_back(j*3+l);
                    }
        memset(dp,0xff,sizeof(dp));
        int ans = 0;
        for(int i = 0;i < n*3;++i)
        {
            if(dp[i] == -1)
                dfs(i);
            ans = max(ans,dp[i]);
        }
        printf("Case %d: maximum height = %d\n",++tcase,ans);
    }
    return 0;
}

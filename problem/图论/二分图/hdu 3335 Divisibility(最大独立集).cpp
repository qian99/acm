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
const int maxn=1000+10;
ll num[maxn];
int G[maxn][maxn],links[maxn],n;
bool vis[maxn];
bool dfs(int u)
{
    for(int i=0;i<n;++i)
    {
        if(G[u][i]&&!vis[i])
        {
            vis[i]=true;
            if(links[i]==-1||dfs(links[i]))
            {
                links[i]=u;
                return true;
            }
        }
    }
    return false;
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
        for(int i=0;i<n;++i)
            scanf("%I64d",&num[i]);
        sort(num,num+n);
        n=unique(num,num+n)-num;
        memset(G,0,sizeof(G));
        for(int i=0;i<n;++i)
            for(int j=0;j<i;++j)
                if(num[i]%num[j]==0||num[j]%num[i]==0)
                    G[i][j]=1;
        memset(links,0xff,sizeof(links));
        int cnt=0;
        for(int i=0;i<n;++i)
        {
            memset(vis,0,sizeof(vis));
            if(dfs(i)) cnt++;
        }
        printf("%d\n",n-cnt);
    }
    return 0;
}

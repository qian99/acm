#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
struct Info
{
    int type,w;
};
vector<int>G[maxn];
int uplim[maxn],downlim[maxn];
bool flag;
void clearAll(int n)
{
    for(int i=0;i<=n;++i) G[i].clear();
    for(int i=1;i<=n;++i)
    {
        uplim[i]=inf;
        downlim[i]=1;
    }
}
void dfs(int u,int fa)
{
    if(!flag) return;
    int sum=0;
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(v!=fa)
        {
            dfs(v,u);
            sum+=downlim[v];
        }
    }
    downlim[u]=max(downlim[u],sum+1);
    if(downlim[u]>uplim[u])
        flag=false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d",&n))
    {
        clearAll(n);
        int a,b;
        char str[2];
        for(int i=2;i<=n;++i)
        {
            scanf("%d",&a);
            G[a].push_back(i);
            G[i].push_back(a);
        }
        flag=true;
        scanf("%d",&m);
        for(int i=0;i<m;++i)
        {
            scanf("%d %s %d",&a,str,&b);
            if(str[0]=='=')
              uplim[a]=downlim[a]=b;
            else if(str[0]=='<')
              uplim[a]=min(uplim[a],b-1);
            else
              downlim[a]=max(downlim[a],b+1);
        }
        dfs(1,-1);
        if(flag) puts("True");
        else puts("Lie");
    }
    return 0;
}

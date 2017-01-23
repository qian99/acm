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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
vector<int>g[maxn];
int degree[maxn],ans[maxn],tot;
void solve(int n)
{
    tot=0;
    queue<int>q;
    for(int i=1;i<=n;++i)
        if(degree[i]==0) q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        ans[u]=++tot;
        for(int i=0;i<(int)g[u].size();++i)
        {
            int v=g[u][i];
            degree[v]--;
            if(degree[v]==0) q.push(v);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    memset(degree,0,sizeof(degree));
    for(int i=0;i<=n;++i) g[i].clear();
    int u,v;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        degree[v]++;
    }
    solve(n);
    if(tot!=n) printf("No solution\n");
    else
    {
        for(int i=1;i<=n;++i)
        {
            if(i>1) printf(" ");
            printf("%d",ans[i]);
        }
        printf("\n");
    }
    return 0;
}

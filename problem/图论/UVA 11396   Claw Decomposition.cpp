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
const int maxn=300+10;
vector<int>g[maxn];
int color[maxn];
bool bipartite(int u)
{
    for(int i=0;i<g[u].size();++i)
    {
        int v=g[u][i];
        if(color[u]==color[v]) return false;
        if(!color[v])
        {
            color[v]=3-color[u];
            if(!bipartite(v)) return false;
        }
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,a,b;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=0;i<=n;++i)
           g[i].clear();
        int bb=0;
        while(~scanf("%d%d",&a,&b))
        {
            if(a==0&&b==0) break;
            g[a].push_back(b);
            g[b].push_back(a);
            bb++;
        }
        if(3*n!=bb*2)
        {
            printf("NO\n");
            continue;
        }
        memset(color,0,sizeof(color));
        color[1]=1;
        if(bipartite(1))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

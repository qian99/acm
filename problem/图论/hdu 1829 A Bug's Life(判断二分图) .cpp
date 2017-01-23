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
const int maxn=2000+10;
vector<int>G[maxn];
int colors[maxn];
bool dfs(int u)
{
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(colors[u]==colors[v]) return false;
        if(!colors[v])
        {
            colors[v]=3-colors[u];
            if(!dfs(v)) return false;
        }
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n;++i) G[i].clear();
        memset(colors,0,sizeof(colors));
        int a,b;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            G[a].push_back(b);
            G[b].push_back(a);
        }
        bool flag=true;
        for(int i=1;i<=n;++i)
           if(!colors[i])
           {
               colors[i]=1;
               if(!dfs(i)) {flag=false;break;}
           }
        printf("Scenario #%d:\n",tcase);
        if(flag)
          printf("No suspicious bugs found!\n\n");
        else
          printf("Suspicious bugs found!\n\n");
    }
    return 0;
}

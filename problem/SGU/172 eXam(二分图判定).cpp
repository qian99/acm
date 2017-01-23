#include<iostream>
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
const int maxn=200+10;
int colors[maxn],res[maxn];
int a[maxn][maxn];
int n,m;
bool dfs(int u)
{
    for(int i=1;i<=n;++i)
    {
        if(a[u][i])
        {
            if(colors[i]==colors[u]) return false;
            if(!colors[i])
            {
                colors[i]=3-colors[u];
                if(!dfs(i)) return false;
            }
        }
    }
    return true;
}
bool solve()
{
    for(int i=1;i<=n;++i)
      if(!colors[i])
      {
          colors[i]=1;
          if(!dfs(i)) return false;
      }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(a,0,sizeof(a));
    scanf("%d%d",&n,&m);
    int u,v;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&u,&v);
        a[u][v]=a[v][u]=1;
    }
    memset(colors,0,sizeof(colors));
    if(solve())
    {
        int cnt=0;
        for(int i=1;i<=n;++i)
          if(colors[i]==1) res[cnt++]=i;
        printf("yes\n");
        printf("%d\n",cnt);
        for(int i=0;i<cnt;++i)
        {
            if(i) printf(" ");
            printf("%d",res[i]);
        }
        printf("\n");
    }
    else printf("no\n");
    return 0;
}

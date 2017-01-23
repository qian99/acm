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
const int maxn=100+10;
int a[maxn][maxn],b[maxn][maxn],n;
int color[maxn];
bool check(int u)
{
    for(int i=1;i<=n;++i)
    {
        if(i==u||!b[u][i]) continue;
        if(color[u]==color[i]) return false;
        if(!color[i])
        {
            color[i]=3-color[u];
            if(!check(i)) return false;
        }
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        memset(a,0,sizeof(a));
        memset(color,0,sizeof(color));
        for(int i=1;i<=n;++i)
        {
            int v;
            while(~scanf("%d",&v))
            {
                if(v==0) break;
                a[i][v]=1;
            }
        }
        memset(b,0,sizeof(b));
        for(int i=1;i<=n;++i)
          for(int j=1;j<=n;++j)
             if(!a[i][j]||!a[j][i]) b[i][j]=b[j][i]=1;
        bool flag=true;
        for(int i=1;i<=n;++i)
        {
            if(!color[i])
            {
                color[i]=1;
                if(!check(i))
                {
                    flag=false;
                    break;
                }
            }
        }
        if(flag)
          printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

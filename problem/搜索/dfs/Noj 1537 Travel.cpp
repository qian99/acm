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
const int maxn=50;
int a[maxn][maxn];
char str[maxn];
bool vis[maxn];
int n;
bool dfs(int u,int ma,int mb)
{
    if(u==n) return true;
    for(int i=1;i<=n;++i)
    {
        if(!vis[i]&&a[u][i])
        {
            if((str[i-1]=='A'&&ma>0)||(str[i-1]=='B'&&mb>0))
            {
                vis[i]=true;
                if(dfs(i,ma-(str[i-1]=='A'),mb-(str[i-1]=='B')))
                    return true;
                vis[i]=false;
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
        int m,x,y,u,v;
        scanf("%d%d%d%d",&n,&m,&x,&y);
        scanf("%s",str);
        memset(a,0,sizeof(a));
        memset(vis,0,sizeof(vis));
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            a[u][v]=1;
        }
        if(str[0]=='A') x--;
        else y--;
        vis[1]=true;
        if(x>=0&&y>=0&&dfs(1,x,y)) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}

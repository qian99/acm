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
const int maxn=55;
int flag[maxn][maxn];
int vis[maxn][maxn];
int R[maxn],ans,n,k;
struct Node
{
    int x,y;
};
Node node[maxn];
bool cancon()
{
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(!vis[i][j]&&flag[i][j]!=2) return false;
    return true;
}
bool check(int x,int y)
{
    return x>=1&&x<=n&&y>=1&&y<=n;
}
void colored(int u,int v)
{
    int x=node[u].x;
    int y=node[u].y;
    int px,py,r=R[u];
    for(int i=r;i>=1;i--)
    {
        for(int j=y-(r-i);j<=y+(r-i);++j)
        {
            px=x-i;
            py=j;
            if(check(px,py)) vis[px][py]+=v;
            px=x+i;
            if(check(px,py)) vis[px][py]+=v;
        }
    }
    for(int i=y-r;i<=y+r;++i)
    {
        px=x;py=i;
        if(check(px,py)) vis[px][py]+=v;
    }
}
void dfs(int step,int cnt)
{
    if(step>k)
    {
        if(cancon()) ans=min(ans,cnt);
        return ;
    }
    colored(step,1);
    dfs(step+1,cnt+1);
    colored(step,-1);
    dfs(step+1,cnt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        scanf("%d",&k);
        memset(flag,0,sizeof(flag));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=k;++i)
        {
            scanf("%d%d",&node[i].x,&node[i].y);
            flag[node[i].x][node[i].y]=2;
        }
        for(int i=1;i<=k;++i)
          scanf("%d",&R[i]);
        ans=inf;
        dfs(1,0);
        if(ans==inf) printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}

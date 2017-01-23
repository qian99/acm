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
const int maxn=2000+10;
char a[maxn][maxn];
struct Edge
{
    int v,next;
};
Edge edges[maxn*maxn];
int head[maxn],nEdge,n;
bool vis[maxn],finds;
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
bool dfs(int u,int fa)
{
    vis[u]=true;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(vis[v]) continue;
        if(fa!=-1&&a[v-1][fa-1]=='1')
          return true;
        if(dfs(v,u)) return true;
    }
    return false;
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
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        scanf("%d",&n);
        for(int i=0;i<n;++i)
        {
            scanf("%s",a[i]);
            for(int j=0;j<n;++j)
                if(a[i][j]=='1')
                 AddEdge(i+1,j+1);
        }
        finds=false;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;++i)
          if(!vis[i])
          {
              if(dfs(i,-1))
              {
                  finds=true;
                  break;
              }
          }
        printf("Case #%d: ",tcase);
        if(finds) puts("Yes");
        else puts("No");
    }
    return 0;
}

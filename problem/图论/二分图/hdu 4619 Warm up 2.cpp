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
#define inf 2139062143
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
vector<int>G[maxn];
int link[maxn];
bool used[maxn];
struct Points
{
    int x,y;
};
Points ver[maxn],hor[maxn];
bool dfs(int u)
{
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!used[v])
        {
            used[v]=true;
            if(link[v]==-1||dfs(link[v]))
            {
                link[v]=u;
                return true;
            }
        }
    }
    return false;
}
int hungary(int n)
{
    memset(link,-1,sizeof(link));
    int res=0;
    for(int i=0;i<n;++i)
    {
        memset(used,0,sizeof(used));
        if(dfs(i)) res++;
    }
    return res;
}
bool check(int i,int j)
{
    if(hor[i].x==ver[j].x&&hor[i].y==ver[j].y) return true;
    if(hor[i].x+1==ver[j].x&&hor[i].y==ver[j].y) return true;
    if(hor[i].x==ver[j].x&&hor[i].y==ver[j].y+1) return true;
    if(hor[i].x+1==ver[j].x&&hor[i].y==ver[j].y+1) return true;
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        for(int i=0;i<maxn;++i) G[i].clear();
        for(int i=0;i<n;++i)
          scanf("%d%d",&hor[i].x,&hor[i].y);
        for(int i=0;i<m;++i)
          scanf("%d%d",&ver[i].x,&ver[i].y);
        for(int i=0;i<n;++i)
          for(int j=0;j<m;++j)
             if(check(i,j)) G[i].push_back(j);
        int ans=hungary(n);
        printf("%d\n",n+m-ans);
    }
    return 0;
}

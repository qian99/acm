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
const int maxn=1000+10;
int n,m,k,w;
char mat[maxn][11][11];
int g[maxn][maxn];
int cal(int x,int y)
{
    int sum=0;
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            sum+=(mat[x][i][j]!=mat[y][i][j])*w;
    return sum;
}
int dis[maxn],links[maxn],id[maxn];
bool vis[maxn];
vector<pair<int,int> >vt;
bool cmp(int x,int y)
{
    return links[x]<links[y];
}
int prim()
{
    memset(vis,0,sizeof(vis));
    memset(links,0,sizeof(links));
    for(int i=0;i<=k;++i)
    {
        dis[i]=g[0][i];
    }
    vis[0]=true;
    int minnum,pos;
    int sum=0;
    for(int i=0;i<k;++i)
    {
        minnum=maxn;
        for(int j=1;j<=k;++j)
        {
            if(!vis[j]&&minnum>dis[j])
            {
                minnum=dis[j];
                pos=j;
            }
        }
        vis[pos]=true;
        sum+=minnum;
        for(int x=1;x<=k;++x)
        {
            if(g[pos][x]<dis[x])
            {
                if(!vis[x]) links[x]=pos;
                dis[x]=g[pos][x];
            }
        }
    }
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d%d%d",&n,&m,&k,&w);
    for(int i=1;i<=k;++i)
    {
        for(int j=0;j<n;++j)
            scanf("%s",mat[i][j]);
    }
    memset(g,0,sizeof(g));
    for(int i=1;i<=k;++i)
        for(int j=1;j<=k;++j)
            g[i][j]=cal(i,j);
    for(int i=1;i<=k;++i)
        g[0][i]=g[i][0]=n*m;
    int ans=prim();
    printf("%d\n",ans);
    memset(vis,0,sizeof(vis));
    vis[0]=true;
    for(int i=1;i<=k;++i)
    {
        int j;
        for(j=1;j<=k;++j)
            if(!vis[j]&&vis[links[j]]) break;
        printf("%d %d\n",j,links[j]);
        vis[j]=true;
    }
    return 0;
}
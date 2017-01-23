#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=500+10;
int n,m,k;
int city[maxn][maxn],dis[maxn];
bool vis[maxn];
int prim()
{
    for(int i=1;i<=n;++i)
    {
        dis[i]=inf;
        vis[i]=false;
    }
    vis[1]=true;
    for(int i=1;i<=n;++i)
    {
        dis[i]=city[1][i];
    }
    __int64 sum=0;
    int minnum;
    int pos;
    for(int i=1;i<n;++i)
    {
        minnum=inf;
        for(int j=1;j<=n;++j)
        {
            if(!vis[j]&&minnum>dis[j])
            {
                minnum=dis[j];
                pos=j;
            }
        }
        sum+=minnum;
        vis[pos]=true;
        for(int u=1;u<=n;++u)
        {
            dis[u]=min(dis[u],city[pos][u]);
        }
    }
    if(sum>=inf)
    {
        return -1;
    }
    return (int)sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    //printf("%d\n",inf*500);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                city[i][j]=inf;
            }
            city[i][i]=0;
        }
        int a,b,c;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            if(city[a][b]>c)
            city[a][b]=city[b][a]=c;
        }
        for(int i=0;i<k;++i)
        {
            scanf("%d",&c);
            for(int j=0;j<c;++j)
            {
                scanf("%d",&dis[j]);
            }
            for(int p=0;p<c;++p)
            {
                for(int q=p+1;q<c;++q)
                {
                    city[dis[p]][dis[q]]=city[dis[q]][dis[p]]=0;
                }
            }
        }
        printf("%d\n",prim());
    }
    return 0;
}


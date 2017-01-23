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
const int maxn=1000+10;
double city[maxn][maxn];
double dis[maxn];
bool vis[maxn];
int n;
double dijkstra(int s,int t)
{
    memset(vis,false,sizeof(vis));
    memset(dis,0,sizeof(dis));
    for(int i=1;i<=n;++i)
    {
        dis[i]=city[s][i];
    }
    vis[s]=true;
    dis[s]=1;
    double mind=0;
    int pos;
    for(int i=1;i<n;++i)
    {
        mind=0;
        for(int j=1;j<=n;++j)
        {
            if(!vis[j]&&mind<dis[j])
            {
                mind=dis[j];
                pos=j;
            }
        }
        vis[pos]=true;
        for(int k=1;k<=n;++k)
        {
            if(!vis[k]&&mind*city[pos][k]>dis[k])
            {
                dis[k]=mind*city[pos][k];
            }
        }
    }
    if(fabs(dis[t])<=10e-6)
       return -1;
    else
       return dis[t];
}
int main()
{
     while(~scanf("%d",&n))
     {
         for(int i=1;i<=n;++i)
         {
             for(int j=1;j<=n;++j)
             {
                 scanf("%lf",&city[i][j]);
             }
         }
         int q;
         scanf("%d",&q);
         int st,ed;
         while(q--)
         {
             scanf("%d%d",&st,&ed);
             double res=dijkstra(st,ed);
             if(res>0)
             {
                 printf("%.3lf\n",res);
             }
             else
             {
                 printf("What a pity!\n");
             }
         }
     }
     return 0;
}

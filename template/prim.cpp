#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;

int min(int a,int b);
int max(int a,int b);
const int maxn=99999999;
int dis[105];
int way[105][105];
bool vis[105];
int prim();
int n;

int prim()
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;++i)
    {
        dis[i]=way[1][i];
    }
    vis[1]=true;
    int minnum,pos;
    int sum=0;
    for(int i=1;i<n;++i)
    {
        minnum=maxn;
        for(int j=1;j<=n;++j)
        {
            if(!vis[j]&&minnum>dis[j])
            {
                minnum=dis[j];
                pos=j;
            }
        }
        vis[pos]=true;
        sum+=minnum;
        for(int k=1;k<=n;++k)
        {
            dis[k]=min(way[pos][k],dis[k]);
        }
    }
    return sum;
}

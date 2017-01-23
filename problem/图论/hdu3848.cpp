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
const int maxn=10000+10;
int minlen=inf;
int movelen[maxn];
int treeleaf[maxn];
struct Edge
{
    int t;
    int len;
};
vector<Edge>g[maxn];
void dfs(int u,int f,int step)
{
    int sz=g[u].size();
    int v;
    if(sz==1&&f!=-1)
    {
        movelen[u]=0;
        return;
    }
    int min1=inf,min2=inf;
    int ml=0;
    for(int i=0;i<sz;++i)
    {
        v=g[u][i].t;
        if(v!=f)
        {
            dfs(v,u,step+g[u][i].len);
            movelen[u]=min(movelen[u],movelen[v]+g[u][i].len);
            ml+=movelen[v]+g[u][i].len;
            if(movelen[v]+g[u][i].len<min1)
            {
                swap(min1,min2);
                min1=movelen[v]+g[u][i].len;
            }
            else if(movelen[v]+g[u][i].len>=min1&&movelen[v]+g[u][i].len<min2)
            {
                min2=movelen[v]+g[u][i].len;
            }
        }
    }
    minlen=min(step+ml,minlen);
    if(min1!=inf&&min2!=inf)
    minlen=min(minlen,min1+min2);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,a,b,c;
    while(~scanf("%d",&n))
    {
        minlen=inf;
        if(n==0) break;
        for(int i=0;i<=n;++i)
        {
            g[i].clear();
            movelen[i]=inf;
            treeleaf[i]=0;
        }
        movelen[0]=0;
        Edge temp;
        for(int i=0;i<n-1;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            temp.len=c;
            temp.t=b;
            g[a].push_back(temp);
            temp.t=a;
            g[b].push_back(temp);
            treeleaf[a]++;
            treeleaf[b]++;
        }
        int st;
        for(int i=1;i<=n;++i)
        {
            if(treeleaf[i]==1)
            {
                st=i;
                break;
            }
        }
        dfs(st,-1,0);
        printf("%d\n",minlen);
    }
    return 0;
}

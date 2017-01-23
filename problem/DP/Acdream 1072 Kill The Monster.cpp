/*
* this code is made by qian99
* Problem: 1072
* Verdict: Accepted
* Submission Date: 2014-05-09 22:42:46
* Time: 528 MS
* Memory: 2136 KB
*/
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
int g[maxn][maxn],val[maxn][maxn],n,m,T,K,B;
int sv[maxn][maxn];
int dp[maxn][maxn][6][6];
void update(int &x,int y)
{
    x=max(x,y);
}
int solve()
{
    memset(dp,0xff,sizeof(dp));
    memset(sv,0,sizeof(sv));
    for(int i=1;i<=T;++i)
        for(int j=1;j<=n;++j)
            for(int k=1;k<=n;++k)
                if(g[j][k]!=-1||j==k) sv[i][j]+=val[i][k];
    for(int i=1;i<=n;++i)
    {
        dp[1][i][B][0]=val[1][i];
        if(B) dp[1][i][B-1][5]=sv[1][i];
    }
    for(int t=1;t<T;++t)
        for(int u=1;u<=n;++u)
            for(int i=0;i<=B;++i)
                for(int j=0;j<=5;++j)
                {
                    if(dp[t][u][i][j]==-1) continue;
                    update(dp[t+1][u][i][max(j-1,0)],dp[t][u][i][j]+val[t+1][u]);
                    if(i>0&&j-1<=0)
                    {
                        update(dp[t+1][u][i-1][5],dp[t][u][i][j]+sv[t+1][u]);
                    }
                    for(int v=1;v<=n;++v)
                    {
                        if(g[u][v]==-1||u==v) continue;
                        if(t+g[u][v]>T) continue;
                        int nt=t+g[u][v];
                        update(dp[nt][v][i][max(j-g[u][v],0)],dp[t][u][i][j]+val[nt][v]);
                        if(i>0&&j-g[u][v]<=0)
                            update(dp[nt][v][i-1][5],dp[t][u][i][j]+sv[nt][v]);
                    }
                }
    int maxv=0;
    for(int u=1;u<=n;++u)
        for(int i=0;i<=B;++i)
            for(int j=0;j<=5;++j)
                if(dp[T][u][i][j]>maxv) maxv=dp[T][u][i][j];
    return maxv;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,K;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d%d",&n,&m,&T,&K,&B);
        memset(val,0,sizeof(val));
        memset(g,0xff,sizeof(g));
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            g[u][v]=g[v][u]=w;
        }
        for(int i=0;i<K;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            val[u][v]+=w;
        }
        int ans=solve();
        printf("%d\n",ans);
    }
    return 0;
}

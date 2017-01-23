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
const int maxn=1<<21;
int color[10],bag[25][15],G,B,S;
int dp[maxn],remain[maxn][10];
bool vis[maxn];
int f(int st)
{
    if(vis[st]) return dp[st];
    if(st==((1<<B)-1))
    {
        return 0;
    }
    vis[st]=true;
    int &res=dp[st];
    res=inf;
    for(int i=0;i<B;++i)
    {
        if(!(st&(1<<i)))
        {
            int pt=0;
            for(int j=1;j<=bag[i][0];++j)
              remain[st][bag[i][j]]++;
            for(int j=0;j<=G;++j)
              pt+=remain[st][j]/S;
            for(int j=1;j<=bag[i][0];++j)
              remain[st][bag[i][j]]--;
            if(pt)
            {
                if(res==inf) res=pt+f(st|(1<<i));
                else res=max(res,pt+f(st|(1<<i)));
            }
            else
            {
                if(res==inf) res=pt-f(st|(1<<i));
                else res=max(res,pt-f(st|(1<<i)));
            }
        }
    }
    return res;
}
int main()
{
    //freopen("a.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&G,&B,&S))
    {
        if(G==0&&B==0&&S==0) break;
        for(int i=0;i<B;++i)
        {
            scanf("%d",&bag[i][0]);
            for(int j=1;j<=bag[i][0];++j)
              scanf("%d",&bag[i][j]);
        }
        memset(remain,0,sizeof(remain));
        int total=1<<B,tmp;
        for(int i=0;i<total;++i)
        {
            tmp=i;
            int j=0;
            while(tmp)
            {
                if(tmp&1)
                {
                    for(int k=1;k<=bag[j][0];++k)
                     remain[i][bag[j][k]]++;
                }
                tmp>>=1;
                j++;
            }
            for(j=0;j<=G;++j)
              remain[i][j]%=S;
        }
        memset(vis,0,sizeof(vis));
        int ans=f(0);
        printf("%d\n",ans);
    }
    return 0;
}

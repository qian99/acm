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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1<<20;
int dp[maxn][20],n,m;
bool vis[maxn][20];
int hero[110],type[20],op[20];
char str[5];
int f(int st,int pos)
{
    if(vis[st][pos]) return dp[st][pos];
    vis[st][pos]=true;
    int& ans=dp[st][pos];
    ans=-inf;
    if(type[pos])
    {
        for(int i=0;i<m;++i)
        {
            if((1<<i)&st) continue;
            if(pos==0) ans=max(ans,hero[i]);
            else if(op[pos]==op[pos-1])
                ans=max(ans,hero[i]+f(st|(1<<i),pos-1));
            else ans=max(ans,hero[i]-f(st|(1<<i),pos-1));
        }
    }
    else
    {
        for(int i=0;i<m;++i)
        {
            if((1<<i)&st) continue;
            if(pos==0) ans=max(ans,0);
            else if(op[pos]==op[pos-1])
                ans=max(ans,f(st|(1<<i),pos-1));
            else ans=max(ans,-f(st|(1<<i),pos-1));
        }
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;++i)
        scanf("%d",&hero[i]);
    scanf("%d",&m);
    for(int i=m-1;i>=0;--i)
    {
        scanf("%s%d",str,&op[i]);
        type[i]=(str[0]=='p');
    }
    sort(hero,hero+n);
    for(int i=0;i<m;++i)
        swap(hero[i],hero[n-i-1]);
    int ans=f(0,m-1);
    if(op[m-1]==2) ans=-ans;
    printf("%d\n",ans);
    return 0;
}

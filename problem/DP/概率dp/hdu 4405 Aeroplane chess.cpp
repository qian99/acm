#pragma comment(linker, "/STACK:102400000,102400000")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
double dp[maxn];
bool flag[maxn];
int n,m;
map<int,int>mp;
double f(int x)
{
    if(x>=n) return 0;
    if(flag[x]) return dp[x];
    flag[x]=true;
    if(mp[x]) return dp[x]=f(mp[x]);
    dp[x]=1;
    for(int i=1;i<=6;++i)
        dp[x]+=1.0/6*f(x+i);
    return dp[x];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        memset(flag,0,sizeof(flag));
        mp.clear();
        int x,y;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&x,&y);
            mp[x]=y;
        }
        printf("%.4lf\n",f(0));
    }
    return 0;
}

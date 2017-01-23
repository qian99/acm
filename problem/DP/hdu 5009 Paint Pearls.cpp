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
const int maxn = 50000 + 10;
ll dp[maxn];
int color[maxn],minp[255];
int lastp[maxn];
map<int,int>mp;
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        mp.clear();
        int cnt = 0;
        for(int i = 1;i <= n;++i)
        {
            scanf("%d",&color[i]);
            if(mp.find(color[i]) == mp.end())
            {
                mp[color[i]] = ++cnt;
                color[i] = cnt;
            }
            else
                color[i] = mp[color[i]];
        }
        int m = min(cnt,(int)sqrt(n) + 1);
        memset(lastp,0,sizeof(lastp));
        memset(minp,0,sizeof(minp));
        dp[0] = 0;
        for(int i = 1;i <= n;++i)
        {
            dp[i] = dp[i-1] + 1;
            for(int j = m;j >= 1;--j)
            {
                if(minp[j] > lastp[color[i]])
                    minp[j] = 0;
                if(minp[j-1] && minp[j-1] > lastp[color[i]])
                {
                    if(minp[j] == 0)
                        minp[j] = minp[j-1];
                    else if(dp[minp[j]-1] > dp[minp[j-1]-1])
                        minp[j] = minp[j-1];
                }
                if(minp[j])
                    dp[i] = min(dp[i],dp[minp[j]-1] + (ll)j*j);
            }
            if(!minp[1])
                minp[1] = i;
            else if(dp[i-1] <= dp[minp[1]-1])
                minp[1] = i;
            lastp[color[i]] = i;
        }
        printf("%I64d\n",dp[n]);
    }
    return 0;
}

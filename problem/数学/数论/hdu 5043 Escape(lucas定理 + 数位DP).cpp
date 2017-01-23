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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int mod = 100000009;
int dp[31][11][22][1<<10],prime;
int vis[31][11][22][1<<10];
int num[11][31],x[11],n,T;
int f(int pos,int now,int sum,int limit)
{
    if(now == n)
    {
        now = sum = 0;
        pos--;
        if(pos == -1) return 1;
    }
    if(vis[pos][now][sum][limit] == T) return dp[pos][now][sum][limit];
    vis[pos][now][sum][limit] = T;
    int & res = dp[pos][now][sum][limit] = 0;
    int last = (limit>>now&1)?(prime - 1):num[now][pos],x;
    for(int i = 0;i <= last;++i)
    {
        if(i + sum >= prime) break;
        x = (i != last);
        res += f(pos,now + 1,sum + i,limit | (x<<now));
        if(res >= mod) res -= mod;
    }
    return res;
}
int solve()
{
    memset(num,0,sizeof(num));
    T++;
    int len = 0,cnt;
    for(int i = 0;i < n;++i)
    {
        cnt = 0;
        do
        {
            num[i][cnt++] = x[i]%prime;
            x[i] /= prime;
        }while(x[i]);
        len = max(len,cnt);
    }
    return f(len - 1,0,0,0);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&prime);
        for(int i = 0;i < n;++i)
            scanf("%d",&x[i]);
        int ans = 1;
        for(int i = 0;i < n;++i)
            ans = ans*(x[i] + 1LL)%mod;
        ans -= solve();
        ans = (ans%mod + mod)%mod;
        printf("Case #%d: %d\n",++tcase,ans);
    }
    return 0;
}
